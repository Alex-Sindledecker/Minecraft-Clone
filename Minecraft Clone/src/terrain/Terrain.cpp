#include "pch.h"
#include "Terrain.h"

Terrain::Terrain()
	: generator(0)
{
	srand(0);
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
	if (pos.y < rand() % 2)
		return Block(BlockType::BEDROCK);
	int height = floor(generator.getHeight2D(pos.x, pos.z) * 128);
	float volume = 0;
	if (volume > -0.5)
	{
		if (pos.y == height)
			return Block(BlockType::GRASS);
		if (pos.y < height && pos.y > height - 4)
			return Block(BlockType::DIRT);
		if (pos.y < height)
			return Block(BlockType::STONE);
	}
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
