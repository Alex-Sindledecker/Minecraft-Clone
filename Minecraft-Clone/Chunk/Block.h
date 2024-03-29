#pragma once

#include <cstdint>
#include "../gl.h"

#include "../Utils/Defs.h"

struct Block
{
	uint8_t id;
	uint8_t state;
};

namespace BlockTools
{
	using CompressedBlockVertex = GLuint;
	using BlockList = std::vector<Block>;

	//For testing only
	struct _VertexInfo
	{
		int x, y, z;
		int atlasIndex;
		int normal;
	};

	//For testing only
	static _VertexInfo decompressVertex(int vertex)
	{
		_VertexInfo info;

		info.x = vertex & 0xf;
		info.y = (vertex >> 4) & 0xf;
		info.z = (vertex >> 8) & 0xf;
		info.atlasIndex = (vertex >> 12) & 0xff;
		info.normal = (vertex >> 20) & 0x4;

		return info;
	}

	//Stores x, y, z, and atlasIndex info a single unsigned integer
	CompressedBlockVertex createCompressedBlockVertex(uint x, uint y, uint z, uint atlasIndex, uint normal);
	int getLocalBlockIndex(uint8_t x, uint8_t y, uint8_t z);
	uint8_t getBlockAtlasIndex(Block& block);
	Block getBlock(BlockList* blockList, BlockList* lBlocks, BlockList* rBlocks, BlockList* fBlocks, BlockList* bBlocks, int x, int y, int z);
}