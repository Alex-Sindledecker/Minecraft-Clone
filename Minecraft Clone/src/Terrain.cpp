#include "pch.h"
#include "Terrain.h"

#include <time.h>

Terrain::Terrain(int seed, int render_dist)
{
	setRenderDistance(render_dist);
}

Terrain::~Terrain()
{
	delete m_blocks;
}

void Terrain::setRenderDistance(unsigned int dist)
{
	m_render_dist = dist;
	const int total_blocks = m_render_dist * m_render_dist * pow(CHUNK_SIZE, 4);
	m_blocks = new Block[total_blocks];
	memset(m_blocks, BLOCK_STATE_VOID, total_blocks * sizeof(Block));
}

Block Terrain::getBlock(int x, int y, int z)
{
	int index = flattenIndex(x, y, z);
	if (m_blocks[index].state == BLOCK_STATE_VOID)
		m_blocks[index] = getNoiseBlock(x, y, z);
	return m_blocks[index];
}

void Terrain::setBlock(Block block, int x, int y, int z)
{
	m_blocks[flattenIndex(x, y, z)] = block;
}

int Terrain::flattenIndex(int x, int y, int z) const
{
	glm::vec3 local = globalToLocal(x, y, z);
	int size = m_render_dist * CHUNK_SIZE;
	int y_size = CHUNK_SIZE * CHUNK_SIZE;
	return local.z * size * y_size + local.y * size + local.x;
}

glm::vec3 Terrain::globalToLocal(int x, int y, int z) const
{
	int half_size = m_render_dist * CHUNK_SIZE * 0.5;
	return glm::vec3((x + half_size) % half_size * 2, (y + half_size) % half_size * 2, (z + half_size) % half_size * 2);
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
