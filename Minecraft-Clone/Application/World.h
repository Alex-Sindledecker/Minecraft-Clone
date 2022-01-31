#pragma once

#include "../Chunk/Chunk.h"

#include "../Cameras/FpsCamera.h"

class World
{
public:
	static World& get();

	void init();
	void update(float dt);
	void render();

	World(World const&) = delete;
	void operator=(World const&) = delete;

private:
	World() {}
	~World() {}

	void buildChunkMesh(int x, int z);

private:
	std::vector<std::vector<Chunk>> chunks;
	FpsCamera camera;
	glm::vec3 origin;

	int chunkIndexOffsetX = 0;
	int chunkIndexOffsetZ;
};