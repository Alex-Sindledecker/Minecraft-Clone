#pragma once

#include "../gl.h"
#include <GLFW/glfw3.h>

#include "Block.h"

class ChunkMesh
{
public:
	ChunkMesh() : vao(0), vbo(0), vertexCount(0) {}
	ChunkMesh(const ChunkMesh& mesh);
	ChunkMesh(ChunkMesh&& mesh) noexcept;

	void init();
	void deinit();
	void buildMesh(BlockTools::BlockList& blocks, BlockTools::BlockList nearChunks[4]);
	void render();

	const int getVertexCount() const;

	void operator=(const ChunkMesh& mesh);
	void operator=(ChunkMesh&& mesh) noexcept;

private:
	gl::VertexArray vao;
	gl::Buffer vbo;
	unsigned int vertexCount;
};