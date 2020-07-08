#include "pch.h"
#include "Chunk.h"

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
	ChunkMesh mesh = ChunkBuilder::buildMesh(m_terrain, m_pos);

	if (mesh.num_quads > 0)
	{
		m_tri_count = mesh.num_quads * 2 * 6;

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, mesh.num_quads * sizeof(Quad), &mesh.mesh.get()[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Chunk::t_render()
{
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, m_tri_count);
	glBindVertexArray(0);
}