#include "ChunkMesh.h"

//For a 15x15x256 chunk: 
//Bytes ber chunk    *  # of chunks
//(15 * 15 * 255 * 2) * (15 * 15) = 25.81875MB
//Bytes for the chunk mesh buffer
//15 * 15 * 255 * 36 * 4 = 8.262MB
//Total expected memory usage in MB: 34.08075MB

#include <iostream>

std::vector<BlockTools::CompressedBlockVertex> ChunkMesh::blockMeshBuffer;
std::condition_variable ChunkMesh::cv;
std::mutex ChunkMesh::mutex;
bool ChunkMesh::meshBufferAvailible = true;

ChunkMesh::ChunkMesh(const ChunkMesh& mesh)
{
	vao = mesh.vao;
	vbo = mesh.vbo;
 	vertexCount = mesh.vertexCount;
}

ChunkMesh::ChunkMesh(ChunkMesh&& mesh) noexcept
{
	vao = mesh.vao;
	vbo = mesh.vbo;
	vertexCount = mesh.vertexCount;

	mesh.vao = 0;
	mesh.vbo = 0;
}

void ChunkMesh::init()
{
	vbo = gl::createBuffer(GL_ARRAY_BUFFER, nullptr, 0, GL_DYNAMIC_DRAW);

	gl::VertexAttribute att;
	att.buffer = vbo;
	att.bufferType = GL_ARRAY_BUFFER;
	att.dataType = GL_UNSIGNED_INT;
	att.divisor = 0;
	att.elements = 1;
	att.offset = (void*)0;
	att.stride = sizeof(BlockTools::CompressedBlockVertex);

	vao = gl::createVertexArray({ att });

	if (blockMeshBuffer.capacity() == 0)
		blockMeshBuffer.reserve(CHUNK_WIDTH * CHUNK_WIDTH * WORLD_HEIGHT * 36);
}

void ChunkMesh::deinit()
{
 	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void ChunkMesh::buildMesh(BlockTools::BlockList* blocks, BlockTools::BlockList* nearChunks[4])
{
	meshAssembled = false;

	meshBuildPtrs.blocks = blocks;
	meshBuildPtrs.lBlocks = nearChunks[LEFT_BLOCK];
	meshBuildPtrs.rBlocks = nearChunks[RIGHT_BLOCK];
	meshBuildPtrs.fBlocks = nearChunks[FRONT_BLOCK];
	meshBuildPtrs.bBlocks = nearChunks[BACK_BLOCK];

	meshAssemblyFuture = std::async(std::launch::async, assembleMesh, &meshBuildPtrs);

	if (meshBufferAvailible)
		cv.notify_one();
}

void ChunkMesh::assembleMesh(MeshBuildPtrs* meshBuildPtrs)
{
	std::unique_lock<std::mutex> lk(mutex);

	cv.wait(lk);

	meshBufferAvailible = false;

	int index = 0;
	for (unsigned int y = 0; y < WORLD_HEIGHT; y++)
	{
		for (unsigned int x = 0; x < CHUNK_WIDTH; x++)
		{
			for (unsigned int z = 0; z < CHUNK_WIDTH; z++)
			{
				int i = BlockTools::getLocalBlockIndex(x, y, z);

				//Don't make a mesh for this block if there's nothing there
				if (meshBuildPtrs->blocks->at(i).id == BLOCK_ID_AIR)
					continue;

				//Vertex compression

				BlockTools::CompressedBlockVertex vertex0 = BlockTools::createCompressedBlockVertex(x, y, z, BlockTools::getBlockAtlasIndex(meshBuildPtrs->blocks->at(i)), 0);
				BlockTools::CompressedBlockVertex vertex1 = BlockTools::createCompressedBlockVertex(x + 1, y, z, BlockTools::getBlockAtlasIndex(meshBuildPtrs->blocks->at(i)), 0);
				BlockTools::CompressedBlockVertex vertex2 = BlockTools::createCompressedBlockVertex(x + 1, y + 1, z, BlockTools::getBlockAtlasIndex(meshBuildPtrs->blocks->at(i)), 0);
				BlockTools::CompressedBlockVertex vertex3 = BlockTools::createCompressedBlockVertex(x, y + 1, z, BlockTools::getBlockAtlasIndex(meshBuildPtrs->blocks->at(i)), 0);

				BlockTools::CompressedBlockVertex vertex4 = BlockTools::createCompressedBlockVertex(x, y, z + 1, BlockTools::getBlockAtlasIndex(meshBuildPtrs->blocks->at(i)), 0);
				BlockTools::CompressedBlockVertex vertex5 = BlockTools::createCompressedBlockVertex(x + 1, y, z + 1, BlockTools::getBlockAtlasIndex(meshBuildPtrs->blocks->at(i)), 0);
				BlockTools::CompressedBlockVertex vertex6 = BlockTools::createCompressedBlockVertex(x + 1, y + 1, z + 1, BlockTools::getBlockAtlasIndex(meshBuildPtrs->blocks->at(i)), 0);
				BlockTools::CompressedBlockVertex vertex7 = BlockTools::createCompressedBlockVertex(x, y + 1, z + 1, BlockTools::getBlockAtlasIndex(meshBuildPtrs->blocks->at(i)), 0);

				if (BlockTools::getBlock(meshBuildPtrs->blocks, meshBuildPtrs->lBlocks, meshBuildPtrs->rBlocks, meshBuildPtrs->fBlocks, meshBuildPtrs->bBlocks, x, y, z - 1).id == BLOCK_ID_AIR)
				{
					//Front face
					blockMeshBuffer.push_back(vertex0 | NORMAL_FRONT);
					blockMeshBuffer.push_back(vertex1 | NORMAL_FRONT);
					blockMeshBuffer.push_back(vertex2 | NORMAL_FRONT);
					blockMeshBuffer.push_back(vertex2 | NORMAL_FRONT);
					blockMeshBuffer.push_back(vertex3 | NORMAL_FRONT);
					blockMeshBuffer.push_back(vertex0 | NORMAL_FRONT);
				}

				if (BlockTools::getBlock(meshBuildPtrs->blocks, meshBuildPtrs->lBlocks, meshBuildPtrs->rBlocks, meshBuildPtrs->fBlocks, meshBuildPtrs->bBlocks, x + 1, y, z).id == BLOCK_ID_AIR)
				{
					//Right face
					blockMeshBuffer.push_back(vertex1 | NORMAL_RIGHT);
					blockMeshBuffer.push_back(vertex5 | NORMAL_RIGHT);
					blockMeshBuffer.push_back(vertex6 | NORMAL_RIGHT);
					blockMeshBuffer.push_back(vertex6 | NORMAL_RIGHT);
					blockMeshBuffer.push_back(vertex2 | NORMAL_RIGHT);
					blockMeshBuffer.push_back(vertex1 | NORMAL_RIGHT);
				}

				if (BlockTools::getBlock(meshBuildPtrs->blocks, meshBuildPtrs->lBlocks, meshBuildPtrs->rBlocks, meshBuildPtrs->fBlocks, meshBuildPtrs->bBlocks, x, y, z + 1).id == BLOCK_ID_AIR)
				{
					//Back face
					blockMeshBuffer.push_back(vertex7 | NORMAL_BACK);
					blockMeshBuffer.push_back(vertex6 | NORMAL_BACK);
					blockMeshBuffer.push_back(vertex5 | NORMAL_BACK);
					blockMeshBuffer.push_back(vertex5 | NORMAL_BACK);
					blockMeshBuffer.push_back(vertex4 | NORMAL_BACK);
					blockMeshBuffer.push_back(vertex7 | NORMAL_BACK);
				}

				if (BlockTools::getBlock(meshBuildPtrs->blocks, meshBuildPtrs->lBlocks, meshBuildPtrs->rBlocks, meshBuildPtrs->fBlocks, meshBuildPtrs->bBlocks, x - 1, y, z).id == BLOCK_ID_AIR)
				{
					//Left face
					blockMeshBuffer.push_back(vertex4 | NORMAL_LEFT);
					blockMeshBuffer.push_back(vertex0 | NORMAL_LEFT);
					blockMeshBuffer.push_back(vertex3 | NORMAL_LEFT);
					blockMeshBuffer.push_back(vertex3 | NORMAL_LEFT);
					blockMeshBuffer.push_back(vertex7 | NORMAL_LEFT);
					blockMeshBuffer.push_back(vertex4 | NORMAL_LEFT);
				}

				if (BlockTools::getBlock(meshBuildPtrs->blocks, meshBuildPtrs->lBlocks, meshBuildPtrs->rBlocks, meshBuildPtrs->fBlocks, meshBuildPtrs->bBlocks, x, y - 1, z).id == BLOCK_ID_AIR)
				{
					//Bottom face
					blockMeshBuffer.push_back(vertex4 | NORMAL_DOWN);
					blockMeshBuffer.push_back(vertex5 | NORMAL_DOWN);
					blockMeshBuffer.push_back(vertex1 | NORMAL_DOWN);
					blockMeshBuffer.push_back(vertex1 | NORMAL_DOWN);
					blockMeshBuffer.push_back(vertex0 | NORMAL_DOWN);
					blockMeshBuffer.push_back(vertex4 | NORMAL_DOWN);
				}

				if (BlockTools::getBlock(meshBuildPtrs->blocks, meshBuildPtrs->lBlocks, meshBuildPtrs->rBlocks, meshBuildPtrs->fBlocks, meshBuildPtrs->bBlocks, x, y + 1, z).id == BLOCK_ID_AIR)
				{
					//Top face
					blockMeshBuffer.push_back(vertex3 | NORMAL_UP);
					blockMeshBuffer.push_back(vertex2 | NORMAL_UP);
					blockMeshBuffer.push_back(vertex6 | NORMAL_UP);
					blockMeshBuffer.push_back(vertex6 | NORMAL_UP);
					blockMeshBuffer.push_back(vertex7 | NORMAL_UP);
					blockMeshBuffer.push_back(vertex3 | NORMAL_UP);
				}

				index += 8;
			}
		}
	}
}

void ChunkMesh::fillVBO()
{
	std::unique_lock<std::mutex> lk(mutex);

	vertexCount = blockMeshBuffer.size();

	if (blockMeshBuffer.capacity() > CHUNK_WIDTH * CHUNK_WIDTH * WORLD_HEIGHT * 36)
		std::cout << "WARNING: BLOCK MESH BUFFER CAPACITY EXCEEDED!!!" << std::endl;

	gl::setBufferData(vbo, GL_ARRAY_BUFFER, blockMeshBuffer.data(), blockMeshBuffer.size() * sizeof(BlockTools::CompressedBlockVertex), GL_DYNAMIC_DRAW);

	blockMeshBuffer.clear();

	meshBufferAvailible = true;
}

void ChunkMesh::render()
{
	if (meshAssembled)
		gl::drawArrays(vao, vertexCount);
	else
	{
		if (meshAssemblyFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
		{
			fillVBO();
			cv.notify_one();
			meshAssembled = true;
		}
	}
}

const int ChunkMesh::getVertexCount() const
{
	return vertexCount;
}

void ChunkMesh::operator=(const ChunkMesh& mesh)
{
	vao = mesh.vao;
	vbo = mesh.vbo;
	vertexCount = mesh.vertexCount;
}

void ChunkMesh::operator=(ChunkMesh&& mesh) noexcept
{
	vao = mesh.vao;
	vbo = mesh.vbo;
	vertexCount = mesh.vertexCount;

	mesh.vao = 0;
	mesh.vbo = 0;
}