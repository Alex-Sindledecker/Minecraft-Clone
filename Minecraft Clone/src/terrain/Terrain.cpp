#include "pch.h"
#include "Terrain.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

Block Terrain::getBlock(int x, int y, int z)
{
	return getBlock(glm::vec3(x, y, z));
}

Block Terrain::getBlock(glm::vec3 pos)
{
	if (m_modified_blocks.find(pos) != m_modified_blocks.end())
	{
		return m_modified_blocks[pos];
	}
	if (pos.y < 10)
		return TerrainGenerator::makeDefaultBlock(BlockType::GRASS);
	return TerrainGenerator::makeDefaultBlock(BlockType::AIR);
}

void Terrain::setBlock(Block block, int x, int y, int z)
{
	setBlock(block, glm::vec3(x, y, z));
}

void Terrain::setBlock(Block block, glm::vec3 pos)
{
	m_modified_blocks[pos] = block;
}
