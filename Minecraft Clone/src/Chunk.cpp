#include "pch.h"
#include "Chunk.h"

#define MIN_MESH_ALLOCATION 3072

Chunk::Chunk(Terrain* terrain, glm::vec3 pos)
	: m_terrain(terrain), m_pos(pos)
{
	m_terrain->getBlock(0, 0, 0);
}

Chunk::~Chunk()
{
}

void Chunk::build()
{
	std::vector<Quad> mesh(MIN_MESH_ALLOCATION);
	unsigned int quadCount = 0;

	for (int z = m_pos.z; z < m_pos.z + CHUNK_SIZE; z++)
	{
		for (int y = m_pos.y; y < m_pos.y + CHUNK_SIZE; y++)
		{
			for (int x = m_pos.x; x < m_pos.x + CHUNK_SIZE; x++)
			{
				if (m_terrain->getBlock(x, y, z).id != BLOCK_ID_AIR)
				{
					int extra_info = fillExtraBlockBytes(m_terrain->getBlock(x, y, z));
					if (m_terrain->getBlock(x + 1, y, z).id == BLOCK_ID_AIR)
					{
						mesh[quadCount] = getRightFace(x, y, z, extra_info);
						quadCount++;
					}
					if (m_terrain->getBlock(x, y + 1, z).id == BLOCK_ID_AIR)
					{
						mesh[quadCount] = getTopFace(x, y, z, extra_info);
						quadCount++;
					}
					if (m_terrain->getBlock(x, y, z + 1).id == BLOCK_ID_AIR)
					{
						mesh[quadCount] = getBackFace(x, y, z, extra_info);
						quadCount++;
					}
					if (m_terrain->getBlock(x - 1, y, z).id == BLOCK_ID_AIR)
					{
						mesh[quadCount] = getLeftFace(x, y, z, extra_info);
						quadCount++;
					}
					if (m_terrain->getBlock(x, y - 1, z).id == BLOCK_ID_AIR)
					{
						mesh[quadCount] = getBottomFace(x, y, z, extra_info);
						quadCount++;
					}
					if (m_terrain->getBlock(x, y, z - 1).id == BLOCK_ID_AIR)
					{
						mesh[quadCount] = getFrontFace(x, y, z, extra_info);
						quadCount++;
					}
				}
			}
		}
	}

	mesh.resize(quadCount);
	mesh.shrink_to_fit();
}

Quad Chunk::getTopFace(int x, int y, int z, int extra_bits)
{
	Quad face;
	face.top_left = glm::vec4(x, y + 1, z + 1, extra_bits);
	face.top_right = glm::vec4(x + 1, y + 1, z + 1, extra_bits);
	face.bottom_left = glm::vec4(x, y + 1, z, extra_bits);
	face.bottom_right = glm::vec4(x, y + 1, z, extra_bits);
	face.top_left2 = face.top_left;
	face.bottom_left2 = face.bottom_left2;
	return face;	
}

Quad Chunk::getBottomFace(int x, int y, int z, int extra_bits)
{
	Quad face;
	face.top_left = glm::vec4(x, y, z + 1, extra_bits);
	face.top_right = glm::vec4(x + 1, y, z + 1, extra_bits);
	face.bottom_left = glm::vec4(x, y, z, extra_bits);
	face.bottom_right = glm::vec4(x, y, z, extra_bits);
	face.top_left2 = face.top_left;
	face.bottom_left2 = face.bottom_left2;
	return face;
}

Quad Chunk::getLeftFace(int x, int y, int z, int extra_bits)
{
	Quad face;
	face.top_left = glm::vec4(x, y + 1, z + 1, extra_bits);
	face.top_right = glm::vec4(x, y + 1, z, extra_bits);
	face.bottom_left = glm::vec4(x, y, z + 1, extra_bits);
	face.bottom_right = glm::vec4(x, y, z, extra_bits);
	face.top_left2 = face.top_left;
	face.bottom_left2 = face.bottom_left2;
	return face;
}

Quad Chunk::getRightFace(int x, int y, int z, int extra_bits)
{
	Quad face;
	face.top_left = glm::vec4(x + 1, y + 1, z + 1, extra_bits);
	face.top_right = glm::vec4(x + 1, y + 1, z, extra_bits);
	face.bottom_left = glm::vec4(x + 1, y, z + 1, extra_bits);
	face.bottom_right = glm::vec4(x + 1, y, z, extra_bits);
	face.top_left2 = face.top_left;
	face.bottom_left2 = face.bottom_left2;
	return face;
}

Quad Chunk::getFrontFace(int x, int y, int z, int extra_bits)
{
	Quad face;
	face.top_left = glm::vec4(x, y + 1, z, extra_bits);
	face.top_right = glm::vec4(x + 1, y + 1, z, extra_bits);
	face.bottom_left = glm::vec4(x, y, z, extra_bits);
	face.bottom_right = glm::vec4(x + 1, y, z, extra_bits);
	face.top_left2 = face.top_left;
	face.bottom_left2 = face.bottom_left2;
	return face;
}

Quad Chunk::getBackFace(int x, int y, int z, int extra_bits)
{
	Quad face;
	face.top_left = glm::vec4(x, y + 1, z + 1, extra_bits);
	face.top_right = glm::vec4(x + 1, y + 1, z + 1, extra_bits);
	face.bottom_left = glm::vec4(x, y, z + 1, extra_bits);
	face.bottom_right = glm::vec4(x + 1, y, z + 1, extra_bits);
	face.top_left2 = face.top_left;
	face.bottom_left2 = face.bottom_left2;
	return face;
}

int Chunk::fillExtraBlockBytes(const Block& block)
{
	byte u = 0;
	byte v = 0;
	byte s = 255;

	int compressed = 0;
	return compressed | (0 + s << 16) | (0 + v << 8) | u;
}
