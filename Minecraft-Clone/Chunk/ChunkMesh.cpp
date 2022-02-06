#include "ChunkMesh.h"

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
}

void ChunkMesh::deinit()
{
 	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void ChunkMesh::buildMesh(BlockTools::BlockList& blocks, BlockTools::BlockList nearChunks[4])
{
	std::vector<BlockTools::CompressedBlockVertex> blockVertices;

	blockVertices.reserve(CHUNK_WIDTH * CHUNK_WIDTH * WORLD_HEIGHT * 36);

	int index = 0;
	for (unsigned int y = 0; y < WORLD_HEIGHT; y++)
	{
		for (unsigned int x = 0; x < CHUNK_WIDTH; x++)
		{
			for (unsigned int z = 0; z < CHUNK_WIDTH; z++)
			{
				int i = BlockTools::getLocalBlockIndex(x, y, z);

				if (blocks[i].id == BLOCK_ID_AIR)
					continue;

				//Vertex compression
				BlockTools::CompressedBlockVertex vertex0 = BlockTools::createCompressedBlockVertex(x, y, z, BlockTools::getBlockAtlasIndex(blocks[i]), 0);
				BlockTools::CompressedBlockVertex vertex1 = BlockTools::createCompressedBlockVertex(x + 1, y, z, BlockTools::getBlockAtlasIndex(blocks[i]), 0);
				BlockTools::CompressedBlockVertex vertex2 = BlockTools::createCompressedBlockVertex(x + 1, y + 1, z, BlockTools::getBlockAtlasIndex(blocks[i]), 0);
				BlockTools::CompressedBlockVertex vertex3 = BlockTools::createCompressedBlockVertex(x, y + 1, z, BlockTools::getBlockAtlasIndex(blocks[i]), 0);

				BlockTools::CompressedBlockVertex vertex4 = BlockTools::createCompressedBlockVertex(x, y, z + 1, BlockTools::getBlockAtlasIndex(blocks[i]), 0);
				BlockTools::CompressedBlockVertex vertex5 = BlockTools::createCompressedBlockVertex(x + 1, y, z + 1, BlockTools::getBlockAtlasIndex(blocks[i]), 0);
				BlockTools::CompressedBlockVertex vertex6 = BlockTools::createCompressedBlockVertex(x + 1, y + 1, z + 1, BlockTools::getBlockAtlasIndex(blocks[i]), 0);
				BlockTools::CompressedBlockVertex vertex7 = BlockTools::createCompressedBlockVertex(x, y + 1, z + 1, BlockTools::getBlockAtlasIndex(blocks[i]), 0);

				if (BlockTools::getBlock(blocks, nearChunks, x, y, z - 1).id == BLOCK_ID_AIR)
				{
					//Front face
					blockVertices.push_back(vertex0 | NORMAL_FRONT);
					blockVertices.push_back(vertex1 | NORMAL_FRONT);
					blockVertices.push_back(vertex2 | NORMAL_FRONT);
					blockVertices.push_back(vertex2 | NORMAL_FRONT);
					blockVertices.push_back(vertex3 | NORMAL_FRONT);
					blockVertices.push_back(vertex0 | NORMAL_FRONT);
				}
				
				if (BlockTools::getBlock(blocks, nearChunks, x + 1, y, z).id == BLOCK_ID_AIR)
				{
					//Right face
					blockVertices.push_back(vertex1 | NORMAL_RIGHT);
					blockVertices.push_back(vertex5 | NORMAL_RIGHT);
					blockVertices.push_back(vertex6 | NORMAL_RIGHT);
					blockVertices.push_back(vertex6 | NORMAL_RIGHT);
					blockVertices.push_back(vertex2 | NORMAL_RIGHT);
					blockVertices.push_back(vertex1 | NORMAL_RIGHT);
				}

				if (BlockTools::getBlock(blocks, nearChunks, x, y, z + 1).id == BLOCK_ID_AIR)
				{
					//Back face
					blockVertices.push_back(vertex7 | NORMAL_BACK);
					blockVertices.push_back(vertex6 | NORMAL_BACK);
					blockVertices.push_back(vertex5 | NORMAL_BACK);
					blockVertices.push_back(vertex5 | NORMAL_BACK);
					blockVertices.push_back(vertex4 | NORMAL_BACK);
					blockVertices.push_back(vertex7 | NORMAL_BACK);
				}

				if (BlockTools::getBlock(blocks, nearChunks, x - 1, y, z).id == BLOCK_ID_AIR)
				{
					//Left face
					blockVertices.push_back(vertex4 | NORMAL_LEFT);
					blockVertices.push_back(vertex0 | NORMAL_LEFT);
					blockVertices.push_back(vertex3 | NORMAL_LEFT);
					blockVertices.push_back(vertex3 | NORMAL_LEFT);
					blockVertices.push_back(vertex7 | NORMAL_LEFT);
					blockVertices.push_back(vertex4 | NORMAL_LEFT);
				}

				if (BlockTools::getBlock(blocks, nearChunks, x, y - 1, z).id == BLOCK_ID_AIR)
				{
					//Bottom face
					blockVertices.push_back(vertex4 | NORMAL_DOWN);
					blockVertices.push_back(vertex5 | NORMAL_DOWN);
					blockVertices.push_back(vertex1 | NORMAL_DOWN);
					blockVertices.push_back(vertex1 | NORMAL_DOWN);
					blockVertices.push_back(vertex0 | NORMAL_DOWN);
					blockVertices.push_back(vertex4 | NORMAL_DOWN);
				}

				if (BlockTools::getBlock(blocks, nearChunks, x, y + 1, z).id == BLOCK_ID_AIR)
				{
					//Top face
					blockVertices.push_back(vertex3 | NORMAL_UP);
					blockVertices.push_back(vertex2 | NORMAL_UP);
					blockVertices.push_back(vertex6 | NORMAL_UP);
					blockVertices.push_back(vertex6 | NORMAL_UP);
					blockVertices.push_back(vertex7 | NORMAL_UP);
					blockVertices.push_back(vertex3 | NORMAL_UP);
				}

				index += 8;
			}
		}
	}

	blockVertices.shrink_to_fit();

	vertexCount = blockVertices.size();

	gl::setBufferData(vbo, GL_ARRAY_BUFFER, blockVertices.data(), blockVertices.size() * sizeof(BlockTools::CompressedBlockVertex), GL_DYNAMIC_DRAW);
}

void ChunkMesh::render()
{
	gl::drawArrays(vao, vertexCount);
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
