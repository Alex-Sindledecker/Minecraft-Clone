#pragma once

#include <stdint.h>

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
	NONE = 0,
	VOID = 255
};

struct Block
{
	BlockType id;
	BlockState state;
};

class TerrainGenerator
{
public:
	static Block makeDefaultBlock(BlockType type);
};

