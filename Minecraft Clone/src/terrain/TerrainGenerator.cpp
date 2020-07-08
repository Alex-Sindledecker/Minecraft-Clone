#include "pch.h"
#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator(const int seed)
{
	m_noise_generator.SetSeed(seed);
}

TerrainGenerator::~TerrainGenerator()
{
}

float TerrainGenerator::getHeight2D(float x, float z) const
{
	return abs(m_noise_generator.GetPerlin(x, z));
}

float TerrainGenerator::getHeight3D(float x, float y, float z) const
{
	return m_noise_generator.GetPerlin(x, y, z);
}
