#pragma once

#include "Terrain.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

struct Triangle
{
	glm::vec4 v1, v2, v3;
};

struct Quad
{
	Triangle t1, t2;
};

class Chunk
{
public:
	Chunk(Terrain* terrain, glm::vec3 pos);
	~Chunk();

	void build();
	void t_render();

private:
	Quad getTopFace( int x, int y, int z, int extra_bits);
	Quad getBottomFace( int x, int y, int z, int extra_bits);
	Quad getLeftFace(int x, int y, int z, int extra_bits);
	Quad getRightFace(int x, int y, int z, int extra_bits);
	Quad getFrontFace(int x, int y, int z, int extra_bits);
	Quad getBackFace(int x, int y, int z, int extra_bits);

	int fillExtraBlockBytes(const Block& block);

	Terrain* m_terrain;
	GLuint m_vao, m_vbo, m_tri_count;
	glm::vec3 m_pos;
};