#pragma once

#include "ChunkMesh.h"

#include "../Cameras/FpsCamera.h"

#include <array>
#include <glm/glm.hpp>

class Chunk
{
public:
	Chunk(glm::vec2 pos);
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

	glm::vec2 getPos();
	void setPos(glm::vec2 pos);

private:
	
	gl::ShaderProgram chunkShader;
	ChunkMesh mesh;

	BlockTools::BlockList blocks;
	glm::vec2 pos;
};