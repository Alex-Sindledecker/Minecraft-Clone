#include "pch.h"
#include "Terrain.h"

Terrain::Terrain()
	: generator(0, 256)
{
}

Terrain::~Terrain()
{
}

Block Terrain::getBlock(int x, int y, int z)
{
	if (m_modified_blocks.find(glm::vec3(x, y, z)) != m_modified_blocks.end())
	{
		return m_modified_blocks[glm::vec3(x, y, z)];
	}
	int height = generator.getHeight2D(x, z);
	if (y == height)
		return Block(BlockType::GRASS);
	if (y < height)
		return Block(BlockType::DIRT);
	return Block(BlockType::AIR);
}

Block Terrain::getBlock(glm::vec3 pos)
{
	if (m_modified_blocks.find(pos) != m_modified_blocks.end())
	{
		return m_modified_blocks[pos];
	}
	int height = generator.getHeight2D(pos.x, pos.z);
	if (pos.y == height)
		return Block(BlockType::GRASS);
	if (pos.y < height)
		return Block(BlockType::DIRT);
	return Block(BlockType::AIR);
}

void Terrain::setBlock(Block block, int x, int y, int z)
{
	setBlock(block, glm::vec3(x, y, z));
}

void Terrain::setBlock(Block block, glm::vec3 pos)
{
	m_modified_blocks[pos] = block;
}
