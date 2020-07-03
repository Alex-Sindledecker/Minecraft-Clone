#include "pch.h"
#include "Chunk.h"

#define MIN_MESH_ALLOCATION 3072

Chunk::Chunk(Terrain* terrain, glm::vec3 pos)
	: m_terrain(terrain), m_pos(pos)
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(GLuint), (void*)0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_tri_count = 0;
}

Chunk::Chunk()
{
	m_pos = glm::vec3(0, 0, 0);
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(GLuint), (void*)0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_tri_count = 0;
}

Chunk::~Chunk()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(2, &m_vao);
}

void Chunk::setTerrain(Terrain* terrain)
{
	m_terrain = terrain;
}

void Chunk::setPosition(glm::vec3 pos)
{
	m_pos = pos;
}

glm::vec3 Chunk::getPosition() const
{
	return m_pos;
}

void Chunk::build()
{
	std::vector<Quad> mesh(MIN_MESH_ALLOCATION);
	unsigned int quadCount = 0;

	for (unsigned int z = 0; z < CHUNK_SIZE; z++)
	{
		for (unsigned int y = 0; y < CHUNK_SIZE; y++)
		{
			for (unsigned int x = 0; x < CHUNK_SIZE; x++)
			{
				Block block = m_terrain->getBlock(x + m_pos.x, y + m_pos.y, z + m_pos.z);
				if (block.id != BLOCK_ID_AIR)
				{
					if (m_terrain->getBlock(x + 1, y, z).id == BLOCK_ID_AIR)
					{
						mesh[quadCount] = getRightFace(x, y, z, block);
						quadCount++;
					}
					if (m_terrain->getBlock(x, y + 1, z).id == BLOCK_ID_AIR)
					{
						mesh[quadCount] = getTopFace(x, y, z, block);
						quadCount++;
					}
					if (m_terrain->getBlock(x, y, z + 1).id == BLOCK_ID_AIR)
					{
						mesh[quadCount] = getBackFace(x, y, z, block);
						quadCount++;
					}
					if (m_terrain->getBlock(x - 1, y, z).id == BLOCK_ID_AIR)
					{
						mesh[quadCount] = getLeftFace(x, y, z, block);
						quadCount++;
					}
					if (m_terrain->getBlock(x, y - 1, z).id == BLOCK_ID_AIR)
					{
 						mesh[quadCount] = getBottomFace(x, y, z, block);
						quadCount++;
					}
					if (m_terrain->getBlock(x, y, z - 1).id == BLOCK_ID_AIR)
					{
						mesh[quadCount] = getFrontFace(x, y, z, block);
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

Quad Chunk::getTopFace(unsigned int x, unsigned int y, unsigned int z, Block& block)
{
	Quad face;
	face.vertices[0] = packData(x + 1, y + 1, z + 1, 0, 0, block);
	face.vertices[1] = packData(x, y + 1, z + 1, 0, 1, block);
	face.vertices[2] = packData(x, y + 1, z, 0, 2, block);
	face.vertices[3] = face.vertices[2];
	face.vertices[4] = packData(x + 1, y + 1, z, 0, 3, block);
	face.vertices[5] = face.vertices[0];
	return face;	
}

Quad Chunk::getBottomFace(unsigned int x, unsigned int y, unsigned int z, Block& block)
{
	Quad face;
	face.vertices[0] = packData(x + 1, y, z + 1, 5, 0, block);
	face.vertices[1] = packData(x, y, z + 1, 5, 1, block);
	face.vertices[2] = packData(x, y, z, 5, 2, block);
	face.vertices[3] = face.vertices[2];
	face.vertices[4] = packData(x + 1, y, z, 5, 3, block);
	face.vertices[5] = face.vertices[0];
	return face;
}

Quad Chunk::getLeftFace(unsigned int x, unsigned int y, unsigned int z, Block& block)
{
	Quad face;
	face.vertices[0] = packData(x, y + 1, z, 2, 0, block);
	face.vertices[1] = packData(x, y + 1, z + 1, 2, 1, block);
	face.vertices[2] = packData(x, y, z + 1, 2, 2, block);
	face.vertices[3] = face.vertices[2];
	face.vertices[4] = packData(x, y, z, 2, 3, block);
	face.vertices[5] = face.vertices[0];
	return face;
}

Quad Chunk::getRightFace(unsigned int x, unsigned int y, unsigned int z, Block& block)
{
	Quad face;
	face.vertices[0] = packData(x + 1, y + 1, z, 4, 0, block);
	face.vertices[1] = packData(x + 1, y + 1, z + 1, 4, 1, block);
	face.vertices[2] = packData(x + 1, y, z + 1, 4, 2, block);
	face.vertices[3] = face.vertices[2];
	face.vertices[4] = packData(x + 1, y, z, 4, 3, block);
	face.vertices[5] = face.vertices[0];
	return face;
}

Quad Chunk::getFrontFace(unsigned int x, unsigned int y, unsigned int z, Block& block)
{
	Quad face;
	face.vertices[0] = packData(x + 1, y + 1, z, 1, 0, block);
	face.vertices[1] = packData(x, y + 1, z, 1, 1, block);
	face.vertices[2] = packData(x, y, z, 1, 2, block);
	face.vertices[3] = face.vertices[2];
	face.vertices[4] = packData(x + 1, y, z, 1, 3, block);
	face.vertices[5] = face.vertices[0];
	return face;
}

Quad Chunk::getBackFace(unsigned int x, unsigned int y, unsigned int z, Block& block)
{
	Quad face;
	face.vertices[0] = packData(x + 1, y + 1, z + 1, 3, 0, block);
	face.vertices[1] = packData(x, y + 1, z + 1, 3, 1, block);
	face.vertices[2] = packData(x, y, z + 1, 3, 2, block);
	face.vertices[3] = face.vertices[2];
	face.vertices[4] = packData(x + 1, y, z + 1, 3, 3, block);
	face.vertices[5] = face.vertices[0];
	return face;
}

#include <random>

unsigned int Chunk::packData(unsigned int x, unsigned int y, unsigned int z, unsigned int normal, unsigned int uv, Block& block) const
{
	unsigned int uv_mod = 0;

	if (block.id == BLOCK_ID_GRASS && normal == 0)
		uv_mod = 0;
	else if (block.id == BLOCK_ID_GRASS && normal > 0 && normal <= 4)
		uv_mod = 1;
	if (block.id == BLOCK_ID_GRASS && normal == 5)
		uv_mod = 2;

	return x | y << 6 | z << 12 | normal << 18 | uv << 21 | uv_mod << 23;
}