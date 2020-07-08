#pragma once

#include "terrain/Terrain.h"

#ifndef MIN_MESH_ALLOCATION
#define MIN_MESH_ALLOCATION 3072
#endif

typedef unsigned int uint;

enum class BlockFace
{
	FRONT,
	BACK,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

struct Quad
{
	uint vertices[6];
};

struct ChunkMesh
{
	std::shared_ptr<Quad> mesh;
	uint num_quads;
};

class ChunkBuilder
{
public:
	static ChunkMesh buildMesh(Terrain* terrain, glm::vec3 chunk_pos);
	static ChunkMesh reduceMesh(ChunkMesh built_mesh);

private:
	ChunkBuilder() {}
	ChunkBuilder(const ChunkBuilder&) {}

	static uint packVertexData(glm::vec3 vertex, uint normal, uint uv_coord, uint8_t uv_index);
	static Quad makeFace(BlockFace face, uint tex_id, glm::vec3 pos);
	static uint getTextureIndex(BlockFace face, BlockType type);
};