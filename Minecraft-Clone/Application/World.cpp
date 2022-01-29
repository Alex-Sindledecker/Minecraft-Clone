#include "World.h"

#include "Application.h"

#include "../Utils/Timer.h"

#include <iostream>

World& World::get()
{
	static World world;
	return world;
}

void World::init()
{
	double blockGenTime = utils::getElapsedTime<utils::Milliseconds>([&]() {
		chunks.emplace_back(glm::vec2(0, 0));
		chunks.emplace_back(glm::vec2(CHUNK_WIDTH, 0));
		chunks.emplace_back(glm::vec2(-1 * CHUNK_WIDTH, 0));
		chunks.emplace_back(glm::vec2(0, -1 * CHUNK_WIDTH));
		chunks.emplace_back(glm::vec2(0, CHUNK_WIDTH));
		chunks.emplace_back(glm::vec2(CHUNK_WIDTH, CHUNK_WIDTH));
		for (int i = 0; i < chunks.size(); i++)
			chunks[i].generateBlocks();
	});
	std::cout << "Block generation took: " << blockGenTime << "ms" << std::endl;
	
	double chunkGenTime = utils::getElapsedTime<utils::Milliseconds>([&]() {
		chunks[0].buildMesh(&chunks[2], &chunks[1], &chunks[4], &chunks[3]);
		chunks[1].buildMesh(&chunks[0], nullptr, nullptr, &chunks[5]);
		chunks[2].buildMesh(nullptr, &chunks[0], nullptr, nullptr);
		chunks[3].buildMesh(nullptr, nullptr, nullptr, &chunks[0]);
		chunks[4].buildMesh(nullptr, &chunks[5], &chunks[0], nullptr);
		chunks[5].buildMesh(&chunks[4], nullptr, &chunks[1], nullptr);
	});
	std::cout << "Chunk generation took: " << chunkGenTime << "ms (~" << chunkGenTime / 5.0 << "ms per Chunk)" << std::endl;

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
