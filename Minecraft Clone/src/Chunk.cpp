#include "pch.h"
#include "Chunk.h"

#define MIN_MESH_ALLOCATION 3072

Chunk::Chunk(Terrain* terrain, glm::vec3 pos)
	: m_terrain(terrain), m_pos(pos)
{
	m_terrain->getBlock(0, 0, 0);
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4(1)), (void*)0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	m_tri_count = mesh.size() * 2 * 6;

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(Quad), &mesh[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Chunk::t_render()
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_tri_count);
	glBindVertexArray(0);
}

Quad Chunk::getTopFace(int x, int y, int z, int extra_bits)
{
	Quad face;
	face.t1.v1 = glm::vec4(x + 1, y + 1, z + 1, extra_bits);
	face.t1.v2 = glm::vec4(x, y + 1, z + 1, extra_bits);
	face.t1.v3 = glm::vec4(x, y + 1, z, extra_bits);
	face.t2.v1 = face.t1.v3;
	face.t2.v2 = glm::vec4(x + 1, y + 1, z, extra_bits);
	face.t2.v3 = face.t1.v1;
	return face;	
}

Quad Chunk::getBottomFace(int x, int y, int z, int extra_bits)
{
	Quad face;
	face.t1.v1 = glm::vec4(x + 1, y, z + 1, extra_bits);
	face.t1.v2 = glm::vec4(x, y, z + 1, extra_bits);
	face.t1.v3 = glm::vec4(x, y, z, extra_bits);
	face.t2.v1 = face.t1.v3;
	face.t2.v2 = glm::vec4(x + 1, y, z, extra_bits);
	face.t2.v3 = face.t1.v1;
	return face;
}

Quad Chunk::getLeftFace(int x, int y, int z, int extra_bits)
{
	Quad face;
	face.t1.v1 = glm::vec4(x, y + 1, z + 1, extra_bits);
	face.t1.v2 = glm::vec4(x, y, z + 1, extra_bits);
	face.t1.v3 = glm::vec4(x, y, z, extra_bits);
	face.t2.v1 = face.t1.v3;
	face.t2.v2 = glm::vec4(x, y + 1, z, extra_bits);
	face.t2.v3 = face.t1.v1;
	return face;
}

Quad Chunk::getRightFace(int x, int y, int z, int extra_bits)
{
	Quad face;
	face.t1.v1 = glm::vec4(x + 1, y + 1, z + 1, extra_bits);
	face.t1.v2 = glm::vec4(x + 1, y, z + 1, extra_bits);
	face.t1.v3 = glm::vec4(x + 1, y, z, extra_bits);
	face.t2.v1 = face.t1.v3;
	face.t2.v2 = glm::vec4(x + 1, y + 1, z, extra_bits);
	face.t2.v3 = face.t1.v1;
	return face;
}

Quad Chunk::getFrontFace(int x, int y, int z, int extra_bits)
{
	Quad face;
	face.t1.v1 = glm::vec4(x + 1, y + 1, z, extra_bits);
	face.t1.v2 = glm::vec4(x, y + 1, z, extra_bits);
	face.t1.v3 = glm::vec4(x, y, z, extra_bits);
	face.t2.v1 = face.t1.v3;
	face.t2.v2 = glm::vec4(x + 1, y, z, extra_bits);
	face.t2.v3 = face.t1.v1;
	return face;
}

Quad Chunk::getBackFace(int x, int y, int z, int extra_bits)
{
	Quad face;
	face.t1.v1 = glm::vec4(x + 1, y + 1, z + 1, extra_bits);
	face.t1.v2 = glm::vec4(x, y + 1, z + 1, extra_bits);
	face.t1.v3 = glm::vec4(x, y, z + 1, extra_bits);
	face.t2.v1 = face.t1.v3;
	face.t2.v2 = glm::vec4(x + 1, y, z + 1, extra_bits);
	face.t2.v3 = face.t1.v1;
	return face;
}

#include <random>

int Chunk::fillExtraBlockBytes(const Block& block)
{
	byte u = rand() % 255;
	byte v = rand() % 255;
	byte s = rand() % 255;

	int compressed = 0;
	return compressed | (0 + s << 16) | (0 + v << 8) | u;
}
