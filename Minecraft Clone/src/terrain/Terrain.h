#pragma once

#include "TerrainGenerator.h"
#include <unordered_map>

class PositionHasher
{
public:
	size_t operator()(const glm::vec3& vector) const
	{
		return vector.x + map_range * (vector.y + map_range * vector.z);
	}

private:
	static const int map_range = INT_MAX;
};

class Terrain
{
public:
	Terrain();
	~Terrain();

	Block getBlock(int x, int y, int z);
	Block getBlock(glm::vec3 pos);
	void setBlock(Block block, int x, int y, int z);
	void setBlock(Block block, glm::vec3 pos);

private:
	TerrainGenerator generator;
	std::unordered_map<glm::vec3, Block, PositionHasher> m_modified_blocks;
};