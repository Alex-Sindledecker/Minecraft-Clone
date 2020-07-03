#pragma once

#include "Terrain.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

struct Quad
{
	GLuint vertices[6];
};

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
	Quad getTopFace(unsigned int x, unsigned int y, unsigned int z, Block& block);
	Quad getBottomFace(unsigned int x, unsigned int y, unsigned int z, Block& block);
	Quad getLeftFace(unsigned int x, unsigned int y, unsigned int z, Block& block);
	Quad getRightFace(unsigned int x, unsigned int y, unsigned int z, Block& block);
	Quad getFrontFace(unsigned int x, unsigned int y, unsigned int z, Block& block);
	Quad getBackFace(unsigned int x, unsigned int y, unsigned int z, Block& block);
	unsigned int packData(unsigned int x, unsigned int y, unsigned int z, unsigned int normal, unsigned int uv, Block& block) const;

	Terrain* m_terrain;
	GLuint m_vao, m_vbo, m_tri_count;
	glm::vec3 m_pos;
};