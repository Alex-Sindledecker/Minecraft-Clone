#include "pch.h"
#include "TerrainGenerator.h"

Block TerrainGenerator::makeDefaultBlock(BlockType type)
{
	Block block;
	block.id = type;
	block.state = BlockState::NONE;
	return block;
}
