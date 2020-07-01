#pragma once

#include "Terrain.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

struct Quad
{
	glm::vec4 top_right;
	glm::vec4 top_left;
	glm::vec4 bottom_left;
	glm::vec4 bottom_left2;
	glm::vec4 bottom_right;
	glm::vec4 top_left2;
	Quad() {}
};

class Chunk
{
public:
	Chunk(Terrain* terrain, glm::vec3 pos);
	~Chunk();

	void build();

private:
	Quad getTopFace( int x, int y, int z, int extra_bits);
	Quad getBottomFace( int x, int y, int z, int extra_bits);
	Quad getLeftFace(int x, int y, int z, int extra_bits);
	Quad getRightFace(int x, int y, int z, int extra_bits);
	Quad getFrontFace(int x, int y, int z, int extra_bits);
	Quad getBackFace(int x, int y, int z, int extra_bits);

	int fillExtraBlockBytes(const Block& block);

	Terrain* m_terrain;
	GLuint m_vao, m_vbo;
	glm::vec3 m_pos;
};