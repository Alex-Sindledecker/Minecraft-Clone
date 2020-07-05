#include "pch.h"
#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator(const int seed, unsigned int max_height)
{
	m_noise_generator.SetSeed(seed);
	this->max_height = max_height;
}

TerrainGenerator::~TerrainGenerator()
{
}

int TerrainGenerator::getHeight2D(float x, float z) const
{
	return abs(m_noise_generator.GetPerlin(x, z) * max_height);
}

float TerrainGenerator::getHeight3D(float x, float y, float z) const
{
	return m_noise_generator.GetPerlin(x, y, z);
}
