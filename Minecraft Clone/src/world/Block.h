#pragma once

typedef unsigned char byte;

enum class BlockType : byte
{
	AIR, GRASS, DIRT, STONE, BEDROCK, WOOD, LEAVES, PLANKS
};

struct Block
{
	BlockType id;
};