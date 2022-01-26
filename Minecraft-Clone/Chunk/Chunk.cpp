#include "Chunk.h"

//TODO: Chunklet regeneration instead of full chunk

Chunk::Chunk(glm::vec3 pos)
	: pos(pos)
{
	blocks.resize(CHUNK_WIDTH * CHUNK_WIDTH * WORLD_HEIGHT);

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

	chunkShader = gl::loadShader("res/shaders/ChunkVertex.glsl", "res/shaders/ChunkFragment.glsl");
}

Chunk::Chunk(Chunk&& chunk) noexcept
{
	vao = chunk.vao;
	vbo = chunk.vbo;
	chunkShader = chunk.chunkShader;
	blocks.swap(chunk.blocks);
	pos = chunk.pos;
	vertexCount = chunk.vertexCount;

	chunk.chunkShader = 0;
	chunk.vao = 0;
	chunk.vbo = 0;
}

Chunk::~Chunk()
{
	glDeleteProgram(chunkShader);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void Chunk::generateBlocks()
{
	for (int y = 0; y < WORLD_HEIGHT; y++)
	{
		for (int x = 0; x < CHUNK_WIDTH; x++)
		{
			for (int z = 0; z < CHUNK_WIDTH; z++)
			{
				int i = BlockTools::getLocalBlockIndex(x, y, z);

				blocks[i].id = BLOCK_ID_GRASS;
			}
		}
	}
}

void Chunk::buildMesh(Chunk* left, Chunk* right, Chunk* front, Chunk* back)
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

void Chunk::render(const FpsCamera& camera)
{
	glUseProgram(chunkShader);
	glUniformMatrix4fv(glGetUniformLocation(chunkShader, "mvp"), 1, GL_FALSE, &camera.getViewProjection()[0][0]);
	gl::drawArrays(vao, vertexCount);
}

glm::vec3 Chunk::getPos()
{
	return pos;
}
