#pragma once

#include "ChunkBuilder.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

class Chunk
{
public:
	Chunk(Terrain* terrain, glm::vec3 pos);
	Chunk();
	~Chunk();

	void setTerrain(Terrain* terrain);
	void setPosition(glm::vec3 pos);
	glm::vec3 getPosition() const;
	void build();
	void t_render();

private:
	Terrain* m_terrain;
	GLuint m_vao, m_vbo, m_tri_count;
	glm::vec3 m_pos;
};