#include "pch.h"
#include "ChunkBuilder.h"

const glm::vec3 vertex_front_top_left = glm::vec3(0, 1, 0);
const glm::vec3 vertex_front_top_right = glm::vec3(1, 1, 0);
const glm::vec3 vertex_front_bottom_left = glm::vec3(0, 0, 0);
const glm::vec3 vertex_front_bottom_right = glm::vec3(1, 0, 0);
const glm::vec3 vertex_back_top_left = glm::vec3(0, 1, 1);
const glm::vec3 vertex_back_top_right = glm::vec3(1, 1, 1);
const glm::vec3 vertex_back_bottom_left = glm::vec3(0, 0, 1);
const glm::vec3 vertex_back_bottom_right = glm::vec3(1, 0, 1);

ChunkMesh ChunkBuilder::buildMesh(Terrain* terrain, glm::vec3 chunk_pos)
{
	Quad* mesh = new Quad[MIN_MESH_ALLOCATION];
	ChunkMesh chunk_mesh;
	chunk_mesh.num_quads = 0;
	chunk_mesh.mesh = std::shared_ptr<Quad>(mesh, [](Quad* q) { delete[] q; });

	for (byte y = 0; y < CHUNK_SIZE; y++)
	{
		for (byte x = 0; x < CHUNK_SIZE; x++)
		{
			for (byte z = 0; z < CHUNK_SIZE; z++)
			{
				glm::vec3 global_pos(x + chunk_pos.x, y + chunk_pos.y, z + chunk_pos.z);
				glm::vec3 local_pos(x, y, z);
				Block this_block = terrain->getBlock(global_pos);
				if (terrain->getBlock(global_pos).id == BlockType::AIR)
					continue;

				if (terrain->getBlock(global_pos.x + 1, global_pos.y, global_pos.z).id == BlockType::AIR)
				{
					mesh[chunk_mesh.num_quads] = makeFace(BlockFace::RIGHT, getTextureIndex(BlockFace::RIGHT, this_block.id), local_pos);
					chunk_mesh.num_quads++;
				}
				if (terrain->getBlock(global_pos.x, global_pos.y + 1, global_pos.z).id == BlockType::AIR)
				{
					mesh[chunk_mesh.num_quads] = makeFace(BlockFace::TOP, getTextureIndex(BlockFace::TOP, this_block.id), local_pos);
					chunk_mesh.num_quads++;
				}
				if (terrain->getBlock(global_pos.x, global_pos.y, global_pos.z + 1).id == BlockType::AIR)
				{
					mesh[chunk_mesh.num_quads] = makeFace(BlockFace::BACK, getTextureIndex(BlockFace::BACK, this_block.id), local_pos);
					chunk_mesh.num_quads++;
				}
				if (terrain->getBlock(global_pos.x - 1, global_pos.y, global_pos.z).id == BlockType::AIR)
				{
					mesh[chunk_mesh.num_quads] = makeFace(BlockFace::LEFT, getTextureIndex(BlockFace::LEFT, this_block.id), local_pos);
					chunk_mesh.num_quads++;
				}
				if (terrain->getBlock(global_pos.x, global_pos.y - 1, global_pos.z).id == BlockType::AIR)
				{
					mesh[chunk_mesh.num_quads] = makeFace(BlockFace::BOTTOM, getTextureIndex(BlockFace::BOTTOM, this_block.id), local_pos);
					chunk_mesh.num_quads++;
				}
				if (terrain->getBlock(global_pos.x, global_pos.y, global_pos.z - 1).id == BlockType::AIR)
				{
					mesh[chunk_mesh.num_quads] = makeFace(BlockFace::FRONT, getTextureIndex(BlockFace::FRONT, this_block.id), local_pos);
					chunk_mesh.num_quads++;
				}
			}
		}
	}

	return chunk_mesh;
}

ChunkMesh ChunkBuilder::reduceMesh(ChunkMesh built_mesh)
{
	return ChunkMesh();
}

uint ChunkBuilder::packVertexData(glm::vec3 vertex, uint normal, uint uv_coord, uint8_t uv_index)
{
	uint x = vertex.x;
	uint y = vertex.y;
	uint z = vertex.z;
	return x | y << 6 | z << 12 | normal << 18 | uv_coord << 21 | uv_index << 23;
}

Quad ChunkBuilder::makeFace(BlockFace face, uint tex_id, glm::vec3 pos)
{
	Quad result;
	switch (face)
	{
	case BlockFace::FRONT:
		result.vertices[0] = packVertexData(pos + vertex_front_top_right, 1, 0, tex_id);
		result.vertices[1] = packVertexData(pos + vertex_front_top_left, 1, 1, tex_id);
		result.vertices[2] = packVertexData(pos + vertex_front_bottom_left, 1, 2, tex_id);
		result.vertices[3] = result.vertices[2];
		result.vertices[4] = packVertexData(pos + vertex_front_bottom_right, 1, 3, tex_id);
		result.vertices[5] = result.vertices[0];
		break;
	case BlockFace::BACK:
		result.vertices[0] = packVertexData(pos + vertex_back_top_right, 3, 0, tex_id);
		result.vertices[1] = packVertexData(pos + vertex_back_top_left, 3, 1, tex_id);
		result.vertices[2] = packVertexData(pos + vertex_back_bottom_left, 3, 2, tex_id);
		result.vertices[3] = result.vertices[2];
		result.vertices[4] = packVertexData(pos + vertex_back_bottom_right, 3, 3, tex_id);
		result.vertices[5] = result.vertices[0];
		break;
	case BlockFace::TOP:
		result.vertices[0] = packVertexData(pos + vertex_back_top_right, 0, 0, tex_id);
		result.vertices[1] = packVertexData(pos + vertex_back_top_left, 0, 1, tex_id);
		result.vertices[2] = packVertexData(pos + vertex_front_top_left, 0, 2, tex_id);
		result.vertices[3] = result.vertices[2];
		result.vertices[4] = packVertexData(pos + vertex_front_top_right, 0, 3, tex_id);
		result.vertices[5] = result.vertices[0];
		break;
	case BlockFace::BOTTOM:
		result.vertices[0] = packVertexData(pos + vertex_back_bottom_right, 5, 0, tex_id);
		result.vertices[1] = packVertexData(pos + vertex_back_bottom_left, 5, 1, tex_id);
		result.vertices[2] = packVertexData(pos + vertex_front_bottom_left, 5, 2, tex_id);
		result.vertices[3] = result.vertices[2];
		result.vertices[4] = packVertexData(pos + vertex_front_bottom_right, 5, 3, tex_id);
		result.vertices[5] = result.vertices[0];
		break;
	case BlockFace::LEFT:
		result.vertices[0] = packVertexData(pos + vertex_front_top_left, 2, 0, tex_id);
		result.vertices[1] = packVertexData(pos + vertex_back_top_left, 2, 1, tex_id);
		result.vertices[2] = packVertexData(pos + vertex_back_bottom_left, 2, 2, tex_id);
		result.vertices[3] = result.vertices[2];
		result.vertices[4] = packVertexData(pos + vertex_front_bottom_left, 2, 3, tex_id);
		result.vertices[5] = result.vertices[0];
		break;
	case BlockFace::RIGHT:
		result.vertices[0] = packVertexData(pos + vertex_front_top_right, 4, 0, tex_id);
		result.vertices[1] = packVertexData(pos + vertex_back_top_right, 4, 1, tex_id);
		result.vertices[2] = packVertexData(pos + vertex_back_bottom_right, 4, 2, tex_id);
		result.vertices[3] = result.vertices[2];
		result.vertices[4] = packVertexData(pos + vertex_front_bottom_right, 4, 3, tex_id);
		result.vertices[5] = result.vertices[0];
		break;
	}
	return result;
}

uint ChunkBuilder::getTextureIndex(BlockFace face, BlockType type)
{
	if (type == BlockType::BEDROCK)
		return 4;
	if (type == BlockType::STONE)
		return 3;
	if (type == BlockType::DIRT || (face == BlockFace::BOTTOM && type == BlockType::GRASS))
		return 2;
	if (type == BlockType::GRASS && face != BlockFace::BOTTOM && face != BlockFace::TOP)
		return 1;
	if (type == BlockType::GRASS)
		return 0;
}
