#pragma once

#include "../gl.h"
#include <GLFW/glfw3.h>
#include <future>
#include <mutex>

#include "Block.h"

class ChunkMesh
{
	struct MeshBuildPtrs
	{
		BlockTools::BlockList* blocks;
		BlockTools::BlockList* lBlocks, * rBlocks, * fBlocks, * bBlocks;
	};
public:
	ChunkMesh() : vao(0), vbo(0), vertexCount(0) {}
	ChunkMesh(const ChunkMesh& mesh);
	ChunkMesh(ChunkMesh&& mesh) noexcept;

	void init();
	void deinit();
	//Sets the info required for the mesh to be succesfully built. If the mesh assembly thread is availible, the mesh will be assembled
	void buildMesh(BlockTools::BlockList* blocks, BlockTools::BlockList* nearChunks[4]);
	void render();

	const int getVertexCount() const;

	void operator=(const ChunkMesh& mesh);
	void operator=(ChunkMesh&& mesh) noexcept;

private:
	//Assembles the vertices of a mesh (async)
	static void assembleMesh(MeshBuildPtrs* meshBuildPtrs);
	//Once a mesh has been assembled, this function is called to move the vertex data into the vbo
	void fillVBO();

private:
	static std::vector<BlockTools::CompressedBlockVertex> blockMeshBuffer;
	static std::condition_variable cv;
	static std::mutex mutex;
	static bool meshBufferAvailible;

	std::future<void> meshAssemblyFuture;
	bool meshAssembled = false;

	MeshBuildPtrs meshBuildPtrs;
	gl::VertexArray vao;
	gl::Buffer vbo;
	unsigned int vertexCount;
};