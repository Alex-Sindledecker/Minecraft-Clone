#include "World.h"

#include "Application.h"

#include <iostream>

World& World::get()
{
	static World world;
	return world;
}

void World::init()
{
	chunks.push_back(Chunk(glm::vec3(0, 0, 0)));
	chunks[0].generateBlocks();
	chunks[0].buildMesh(nullptr, nullptr, nullptr, nullptr);

	gl::enableWireframeDraw();

	camera.updateProjection();
}

void World::update(float dt)
{
	camera.update(dt);
	camera.updateView();
}

void World::render()
{
	chunks[0].render(camera);
}
