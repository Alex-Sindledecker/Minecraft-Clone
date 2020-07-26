#include "pch.h"
#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator(unsigned int world_height, unsigned int seed)
	: m_world_height(world_height)
{
	m_noise_gen.SetSeed(seed);
	m_noise_gen.SetInterp(FastNoise::Interp::Hermite);
}

TerrainGenerator::~TerrainGenerator()
{
}

Block TerrainGenerator::getBlock(float x, float y, float z)
{
	float height_variation = 0;
	switch (getBiome(x, z))
	{
	case BiomeType::PLAINS:
		m_noise_gen.SetFrequency(0.001);
		height_variation = 20;
		break;
	case BiomeType::MOUNTAINS:
		m_noise_gen.SetFrequency(0.1);
		height_variation = 128;
		break;
	case BiomeType::FOREST:
		m_noise_gen.SetFrequency(0.01);
		height_variation = 40;
		break;
	}

	float height = floor((m_noise_gen.GetSimplex(x, z) + 1.f) / 2.f * height_variation);
	if (y > height)
		return { BlockType::AIR };
	if (y == height)
		return { BlockType::GRASS };
	if (y > height - 5)
		return { BlockType::DIRT };
	if (y == 0)
		return { BlockType::BEDROCK };
	return { BlockType::STONE };
}

BiomeType TerrainGenerator::getBiome(float x, float z)
{
	m_noise_gen.SetFrequency(0.0001);
	float elevation = m_noise_gen.GetSimplex(x, z);
	if (elevation < -0.4)
		return BiomeType::PLAINS;
	if (elevation < 0.4)
		return BiomeType::FOREST;
	return BiomeType::MOUNTAINS;
}
