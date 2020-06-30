#include "pch.h"
#include "Terrain.h"

#include <time.h>

Terrain::Terrain(int seed, int render_dist)
{
	setRenderDistance(render_dist);
	update(glm::vec3(0, 0, 0));
}

Terrain::~Terrain()
{
}

void Terrain::setRenderDistance(unsigned int dist)
{
	m_render_dist = dist;
	int totalBlocks = m_render_dist * m_render_dist * pow(CHUNK_SIZE, 4);
	m_blocks.resize(totalBlocks);
}

Block Terrain::getBlock(int x, int y, int z)
{
	return m_blocks[flattenIndex(x, y, z)];
}

void Terrain::setBlock(Block block, int x, int y, int z)
{
	m_blocks[flattenIndex(x, y, z)] = block;
}

void Terrain::update(glm::vec3 pos)
{
	for (int y = 0; y < CHUNK_SIZE * CHUNK_SIZE; y++)
	{
		for (int x = 0; x < m_render_dist * CHUNK_SIZE; x++)
		{
			for (int z = 0; z < m_render_dist * CHUNK_SIZE; z++)
			{
				m_blocks[flattenIndex(x, y, z)] = getNoiseBlock(x, y, z);
			}
		}
	}
}

int Terrain::flattenIndex(int x, int y, int z) const
{
	int size = m_render_dist * CHUNK_SIZE;
	int y_size = CHUNK_SIZE * CHUNK_SIZE;
	return z * size * y_size + y * size + x;
}

Block Terrain::getNoiseBlock(int x, int y, int z) const
{
	Block block;
	if (y < 16)
	{
		block.id = BLOCK_ID_GRASS;
		block.state = BLOCK_STATE_NONE;
	}
	else
	{
		block.id = BLOCK_ID_AIR;
		block.state = BLOCK_STATE_NONE;
	}
	return block;
}
