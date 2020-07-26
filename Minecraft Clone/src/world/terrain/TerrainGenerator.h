#pragma once

#include "FastNoise/FastNoise.h"
#include "world/Block.h"

enum class BiomeType
{
	PLAINS,
	MOUNTAINS,
	FOREST
};

class TerrainGenerator
{
public:
	TerrainGenerator(unsigned int world_height, unsigned int seed = 0);
	~TerrainGenerator();

	Block getBlock(float x, float y, float z);

private:
	BiomeType getBiome(float x, float z);

	FastNoise m_noise_gen;
	const unsigned int m_world_height;
};

