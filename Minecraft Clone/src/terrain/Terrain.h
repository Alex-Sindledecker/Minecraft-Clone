#pragma once

#include <vector>

typedef uint8_t byte;
constexpr unsigned int CHUNK_SIZE = 16;
constexpr byte BLOCK_ID_AIR = 0;
constexpr byte BLOCK_ID_GRASS = 1;
constexpr byte BLOCK_STATE_NONE = 0;
constexpr byte BLOCK_STATE_VOID = 255;

struct Block
{
	byte id;
	byte state;
};

class Terrain
{
public:
	Terrain(int seed, int render_dist);
	~Terrain();

	void setRenderDistance(unsigned int dist);
	Block getBlock(int x, int y, int z);
	void setBlock(Block block, int x, int y, int z);

private:
	int flattenIndex(int x, int y, int z) const;
	glm::vec3 globalToLocal(int x, int y, int z) const;
	Block getNoiseBlock(int x, int y, int z) const;

	Block* m_blocks;
	unsigned int m_render_dist;
};