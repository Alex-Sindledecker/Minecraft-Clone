#pragma once

#include "../gl.h"
#include <GLFW/glfw3.h>

#include "../Cameras/FpsCamera.h"

#include <array>
#include <glm/glm.hpp>

#include "Block.h"

class Chunk
{
public:
	Chunk(glm::vec3 pos);
	//Move constructor (move the contents of 'chunk' into this chunk)
	Chunk(Chunk&& chunk) noexcept;
	~Chunk();

	void generateBlocks();
	/*
	* For when world saving is added
	void fetchBlocks()
	*/
	void buildMesh(Chunk* left, Chunk* right, Chunk* front, Chunk* back);

	void render(const FpsCamera& camera);

	glm::vec3 getPos();

private:
	gl::VertexArray vao;
	gl::Buffer vbo;
	gl::ShaderProgram chunkShader;
	unsigned int vertexCount;

	std::vector<Block> blocks;
	glm::vec3 pos;
};