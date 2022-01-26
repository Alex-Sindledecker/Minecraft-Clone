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
	glGenBuffers(1, &vbo);

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

				BlockTools::CompressedBlockVertex vertex1 = BlockTools::createCompressedBlockVertex(x, y, z, BlockTools::getBlockAtlasIndex(blocks[i]), 0);
				BlockTools::CompressedBlockVertex vertex2 = BlockTools::createCompressedBlockVertex(x + 1, y, z, BlockTools::getBlockAtlasIndex(blocks[i]), 0);
				BlockTools::CompressedBlockVertex vertex3 = BlockTools::createCompressedBlockVertex(x + 1, y + 1, z, BlockTools::getBlockAtlasIndex(blocks[i]), 0);
				BlockTools::CompressedBlockVertex vertex4 = BlockTools::createCompressedBlockVertex(x, y + 1, z, BlockTools::getBlockAtlasIndex(blocks[i]), 0);

				blockVertices.push_back(vertex1);
				blockVertices.push_back(vertex2);
				blockVertices.push_back(vertex3);

				blockVertices.push_back(vertex3);
				blockVertices.push_back(vertex4);
				blockVertices.push_back(vertex1);
			}
		}
	}

	blockVertices.shrink_to_fit();
	vertexCount = blockVertices.size();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, blockVertices.size() * sizeof(BlockTools::CompressedBlockVertex), blockVertices.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
