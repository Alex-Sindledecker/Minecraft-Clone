#include "Chunk.h"

#include "TerrainGenerator.h"

#include <iostream>

Chunk::Chunk(glm::vec2 pos)
	: pos(pos)
{
	blocks.resize(CHUNK_WIDTH * CHUNK_WIDTH * WORLD_HEIGHT);

	mesh.init();

	chunkShader = gl::loadShader("res/shaders/ChunkVertex.glsl", "res/shaders/ChunkFragment.glsl");
}

Chunk::Chunk(Chunk&& chunk) noexcept
{
	mesh = std::move(chunk.mesh);
	chunkShader = chunk.chunkShader;
	blocks.swap(chunk.blocks);
	pos = chunk.pos;

	chunk.chunkShader = 0;
}

Chunk::~Chunk()
{
	mesh.deinit();
	glDeleteProgram(chunkShader);
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

				blocks[i] = Terrain::getBlock(x + pos.x, y, z + pos.y);
				//blocks[i] = { BLOCK_ID_GRASS, 0 };
			}
		}
	}
}

void Chunk::buildMesh(Chunk* left, Chunk* right, Chunk* front, Chunk* back)
{
	BlockTools::BlockList* near[4] = { left == nullptr ? nullptr : &left->blocks,
									  right == nullptr ? nullptr : &right->blocks,
									  front == nullptr ? nullptr : &front->blocks,
									  back == nullptr ? nullptr : &back->blocks };
	mesh.buildMesh(&blocks, near);
}

void Chunk::render(const FpsCamera& camera)
{
	glUseProgram(chunkShader);
	glUniformMatrix4fv(glGetUniformLocation(chunkShader, "mvp"), 1, GL_FALSE, &camera.getViewProjection()[0][0]);
	glUniform2fv(glGetUniformLocation(chunkShader, "chunkPos"), 1, &pos[0]);
	mesh.render();
}

glm::vec2 Chunk::getPos()
{
	return pos;
}

void Chunk::setPos(glm::vec2 pos)
{
	this->pos = pos;
}
