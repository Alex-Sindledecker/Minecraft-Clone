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
	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(GLuint), (void*)0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Chunk::~Chunk()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(2, &m_vao);
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
				Block block = m_terrain->getBlock(x, y, z);
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
	face.vertices[0] = packData(x + 1, y + 1, z + 1, 0, block);
	face.vertices[1] = packData(x, y + 1, z + 1, 0, block);
	face.vertices[2] = packData(x, y + 1, z, 0, block);
	face.vertices[3] = face.vertices[2];
	face.vertices[4] = packData(x + 1, y + 1, z, 0, block);
	face.vertices[5] = face.vertices[0];
	return face;	
}

Quad Chunk::getBottomFace(unsigned int x, unsigned int y, unsigned int z, Block& block)
{
	Quad face;
	face.vertices[0] = packData(x + 1, y, z + 1, 0, block);
	face.vertices[1] = packData(x, y, z + 1, 0, block);
	face.vertices[2] = packData(x, y, z, 0, block);
	face.vertices[3] = face.vertices[2];
	face.vertices[4] = packData(x + 1, y, z, 0, block);
	face.vertices[5] = face.vertices[0];
	return face;
}

Quad Chunk::getLeftFace(unsigned int x, unsigned int y, unsigned int z, Block& block)
{
	Quad face;
	face.vertices[0] = packData(x, y + 1, z + 1, 0, block);
	face.vertices[1] = packData(x, y, z + 1, 0, block);
	face.vertices[2] = packData(x, y, z, 0, block);
	face.vertices[3] = face.vertices[2];
	face.vertices[4] = packData(x, y + 1, z, 0, block);
	face.vertices[5] = face.vertices[0];
	return face;
}

Quad Chunk::getRightFace(unsigned int x, unsigned int y, unsigned int z, Block& block)
{
	Quad face;
	face.vertices[0] = packData(x + 1, y + 1, z + 1, 0, block);
	face.vertices[1] = packData(x + 1, y, z + 1, 0, block);
	face.vertices[2] = packData(x + 1, y, z, 0, block);
	face.vertices[3] = face.vertices[2];
	face.vertices[4] = packData(x + 1, y + 1, z, 0, block);
	face.vertices[5] = face.vertices[0];
	return face;
}

Quad Chunk::getFrontFace(unsigned int x, unsigned int y, unsigned int z, Block& block)
{
	Quad face;
	face.vertices[0] = packData(x + 1, y + 1, z, 0, block);
	face.vertices[1] = packData(x, y + 1, z, 0, block);
	face.vertices[2] = packData(x, y, z, 0, block);
	face.vertices[3] = face.vertices[2];
	face.vertices[4] = packData(x + 1, y, z, 0, block);
	face.vertices[5] = face.vertices[0];
	return face;
}

Quad Chunk::getBackFace(unsigned int x, unsigned int y, unsigned int z, Block& block)
{
	Quad face;
	face.vertices[0] = packData(x + 1, y + 1, z + 1, 0, block);
	face.vertices[1] = packData(x, y + 1, z + 1, 0, block);
	face.vertices[2] = packData(x, y, z + 1, 0, block);
	face.vertices[3] = face.vertices[2];
	face.vertices[4] = packData(x + 1, y, z + 1, 0, block);
	face.vertices[5] = face.vertices[0];
	return face;
}

#include <random>

unsigned int Chunk::packData(unsigned int x, unsigned int y, unsigned int z, unsigned int normal, Block& block) const
{
	byte u = rand() % 255;
	byte v = rand() % 255;
	byte s = rand() % 255;

	return x | y << 5 | z << 10;
}
