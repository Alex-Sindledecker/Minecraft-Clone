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

	std::vector<Chunk> chunks;

	FpsCamera camera;
};