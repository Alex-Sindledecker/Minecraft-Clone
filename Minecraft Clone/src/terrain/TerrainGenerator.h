#pragma once

#include <stdint.h>
#include <FastNoise/FastNoise.h>

typedef uint8_t byte;

enum class BlockType : byte
{
	AIR = 0,
	GRASS,
	DIRT,
	STONE
};

enum class BlockState : byte
{
	NONE = 0
};

struct Block
{
	BlockType id;
	BlockState state;
	Block() : id(BlockType::AIR), state(BlockState::NONE) {}
	Block(BlockType id, BlockState state = BlockState::NONE) : id(id), state(state) {}
};

class TerrainGenerator
{
public:
	TerrainGenerator(const int seed, unsigned int max_height);
	~TerrainGenerator();

	int getHeight2D(float x, float z) const;
	float getHeight3D(float x, float y, float z) const;

private:
	FastNoise m_noise_generator;
	unsigned int max_height;
};

