#pragma once

#include <cstdint>
#include "../gl.h"

constexpr unsigned int CHUNK_WIDTH = 15;
constexpr unsigned int WORLD_HEIGHT = 256;

constexpr unsigned int ATLAS_SIZE = 256;
constexpr unsigned int ATLAS_IMAGE_SIZE = 16;

constexpr uint8_t BLOCK_ID_AIR = 0;
constexpr uint8_t BLOCK_ID_GRASS = 1;
constexpr uint8_t BLOCK_ID_DIRT = 2;
constexpr uint8_t BLOCK_ID_STONE = 3;

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
		int imageCorner;
	};

	//For testing only
	static _VertexInfo decompressVertex(int vertex)
	{
		_VertexInfo info;

		info.x = vertex & 0xf;
		info.y = (vertex >> 4) & 0xf;
		info.z = (vertex >> 8) & 0xf;
		info.atlasIndex = (vertex >> 12) & 0xff;
		info.imageCorner = (vertex >> 20) & 0x3;

		return info;
	}

	//Stores x, y, z, and atlasIndex info a single unsigned integer
	CompressedBlockVertex createCompressedBlockVertex(unsigned int x, unsigned int y, unsigned int z, unsigned int atlasIndex, unsigned int imageCorner);
	int getLocalBlockIndex(uint8_t x, uint8_t y, uint8_t z);
	uint8_t getBlockAtlasIndex(Block& block);
}