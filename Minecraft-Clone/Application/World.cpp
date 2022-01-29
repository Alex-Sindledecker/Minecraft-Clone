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
	chunks.emplace_back(glm::vec3(0, 0, 0));
	chunks.emplace_back(glm::vec3(CHUNK_WIDTH, 0, 0));
	chunks.emplace_back(glm::vec3(-1 * CHUNK_WIDTH, 0, 0));
	chunks.emplace_back(glm::vec3(0, 0, -1 * CHUNK_WIDTH));
	chunks.emplace_back(glm::vec3(0, 0, CHUNK_WIDTH));
	for (int i = 0; i < 5; i++)
		chunks[i].generateBlocks();

	chunks[0].buildMesh(&chunks[2], &chunks[1], &chunks[4], &chunks[3]);
	chunks[1].buildMesh(&chunks[0], nullptr, nullptr, nullptr);
	chunks[2].buildMesh(nullptr, &chunks[0], nullptr, nullptr);
	chunks[3].buildMesh(nullptr, nullptr, nullptr, &chunks[0]);
	chunks[4].buildMesh(nullptr, nullptr, &chunks[0], nullptr);
	

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
	for (int i = 0; i < chunks.size(); i++)
		chunks[i].render(camera);
}
