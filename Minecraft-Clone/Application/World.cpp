#include "World.h"

#include "Application.h"

#include "../Utils/Timer.h"
#include "../Utils/Math.h"

#include <iostream>

World& World::get()
{
	static World world;
	return world;
}

void World::init()
{
	camera.setPos(glm::vec3(0, WORLD_HEIGHT + 10, 0));
	origin = camera.getPos();

	double blockGenTime = utils::getElapsedTime<utils::Milliseconds>([&]() {
		for (int z = 0; z < CHUNK_RENDER_DISTANCE; z++)
		{
			chunks.push_back(std::vector<Chunk>());
			for (int x = 0; x < CHUNK_RENDER_DISTANCE; x++)
			{
				int xPos = x * CHUNK_WIDTH - (CHUNK_RENDER_DISTANCE * CHUNK_WIDTH) / 2.f + origin.z;
				int zPos = z * CHUNK_WIDTH - (CHUNK_RENDER_DISTANCE * CHUNK_WIDTH) / 2.f + origin.z;
				chunks[z].emplace_back(glm::vec2(xPos, zPos));
				chunks[z][x].generateBlocks();
			}
		}
	});
	std::cout << "Block generation took: " << blockGenTime << "ms" << std::endl;
	
	double chunkGenTime = utils::getElapsedTime<utils::Milliseconds>([&]() {
		for (int z = 0; z < CHUNK_RENDER_DISTANCE; z++)
		{
			for (int x = 0; x < CHUNK_RENDER_DISTANCE; x++)
			{
				buildChunkMesh(x, z);
			}
		}
	});
	std::cout << "Chunk generation took: " << chunkGenTime << "ms (~" << chunkGenTime / double(CHUNK_RENDER_DISTANCE * CHUNK_RENDER_DISTANCE) << "ms per Chunk)" << std::endl;

	//gl::enableWireframeDraw();

	camera.updateProjection();
}

void World::update(float dt)
{
	camera.update(dt);
	camera.updateView();

	if (glfwGetKey(Application::get().getWindow(), GLFW_KEY_LEFT_SHIFT))
		camera.setSpeed(20);
	else
		camera.setSpeed(5);

	glm::vec3 distanceFromOrigin = camera.getPos() - origin;

	if (distanceFromOrigin.x > CHUNK_WIDTH)
	{
		double time = utils::getElapsedTime<utils::Milliseconds>([&]() {cycleChunksX(1); });
		std::cout << "Chunk line generation took: " << time << "ms (~" << time / double(CHUNK_RENDER_DISTANCE) << "ms per Chunk)" << std::endl;
	}

	else if (-distanceFromOrigin.x > CHUNK_WIDTH)
	{
		double time = utils::getElapsedTime<utils::Milliseconds>([&]() {cycleChunksX(-1); });
		std::cout << "Chunk line generation took: " << time << "ms (~" << time / double(CHUNK_RENDER_DISTANCE) << "ms per Chunk)" << std::endl;
	}

	if (distanceFromOrigin.z > CHUNK_WIDTH)
	{
		double time = utils::getElapsedTime<utils::Milliseconds>([&]() {cycleChunksZ(1); });
		std::cout << "Chunk line generation took: " << time << "ms (~" << time / double(CHUNK_RENDER_DISTANCE) << "ms per Chunk)" << std::endl;
	}

	else if (-distanceFromOrigin.z > CHUNK_WIDTH)
	{
		double time = utils::getElapsedTime<utils::Milliseconds>([&]() {cycleChunksZ(-1); });
		std::cout << "Chunk line generation took: " << time << "ms (~" << time / double(CHUNK_RENDER_DISTANCE) << "ms per Chunk)" << std::endl;
	}
}

void World::render()
{
	for (int z = 0; z < CHUNK_RENDER_DISTANCE; z++)
	{
		for (int x = 0; x < CHUNK_RENDER_DISTANCE; x++)
		{
			chunks[z][x].render(camera);
		}
	}
}

void World::cycleChunksX(int dir)
{
	int x = chunkIndexOffsetX;
	chunkIndexOffsetX = utils::loopMod(chunkIndexOffsetX + dir, CHUNK_RENDER_DISTANCE);

	int cycleEnd = utils::loopMod(x - 1, CHUNK_RENDER_DISTANCE);
	int cycleA = x, cycleB = cycleEnd;

	if (dir == -1)
	{
		cycleA = cycleEnd;
		cycleB = x;
	}

	for (int z = 0; z < CHUNK_RENDER_DISTANCE; z++)
	{
		chunks[z][cycleA].setPos(chunks[z][cycleB].getPos() + glm::vec2(CHUNK_WIDTH * dir, 0));

		chunks[z][cycleA].generateBlocks();
		buildChunkMesh(cycleA, z);
	}

	origin.x += CHUNK_WIDTH * dir;
}

void World::cycleChunksZ(int dir)
{
	int z = chunkIndexOffsetZ;
	chunkIndexOffsetZ = utils::loopMod(chunkIndexOffsetZ + dir, CHUNK_RENDER_DISTANCE);

	int cycleEnd = utils::loopMod(z - 1, CHUNK_RENDER_DISTANCE);
	int cycleA = z, cycleB = cycleEnd;

	if (dir == -1)
	{
		cycleA = cycleEnd;
		cycleB = z;
	}

	for (int x = 0; x < CHUNK_RENDER_DISTANCE; x++)
	{
		chunks[cycleA][x].setPos(chunks[cycleB][x].getPos() + glm::vec2(0, CHUNK_WIDTH * dir));

		chunks[cycleA][x].generateBlocks();
		buildChunkMesh(x, cycleA);
	}

	origin.z += CHUNK_WIDTH * dir;
}

void World::buildChunkMesh(int x, int z)
{
	Chunk* l, * r, * f, * b;

	int shiftEndX = utils::loopMod(chunkIndexOffsetX - 1, CHUNK_RENDER_DISTANCE);
	int shiftEndZ = utils::loopMod(chunkIndexOffsetZ - 1, CHUNK_RENDER_DISTANCE);

	l = x == chunkIndexOffsetX ? nullptr : &chunks[z][utils::loopMod(x - 1, CHUNK_RENDER_DISTANCE)];
	r = x == shiftEndX ? nullptr : &chunks[z][utils::loopMod(x + 1, CHUNK_RENDER_DISTANCE)];

	b = z == shiftEndZ ? nullptr : &chunks[utils::loopMod(z + 1, CHUNK_RENDER_DISTANCE)][x];
	f = z == chunkIndexOffsetZ ? nullptr : &chunks[utils::loopMod(z - 1, CHUNK_RENDER_DISTANCE)][x];

	chunks[z][x].buildMesh(l, r, f, b);
}