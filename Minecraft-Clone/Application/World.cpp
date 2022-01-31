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
	double blockGenTime = utils::getElapsedTime<utils::Milliseconds>([&]() {
		for (int z = 0; z < CHUNK_RENDER_DISTANCE; z++)
		{
			chunks.push_back(std::vector<Chunk>());
			for (int x = 0; x < CHUNK_RENDER_DISTANCE; x++)
			{
				chunks[z].emplace_back(glm::vec2(x * CHUNK_WIDTH - (CHUNK_RENDER_DISTANCE * CHUNK_WIDTH) / 2.f, z * CHUNK_WIDTH - (CHUNK_RENDER_DISTANCE * CHUNK_WIDTH) / 2.f));
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

	gl::enableWireframeDraw();

	camera.updateProjection();

	origin = camera.getPos();
}

void World::update(float dt)
{
	camera.update(dt);
	camera.updateView();

	glm::vec3 distanceFromOrigin = camera.getPos() - origin;

	if (distanceFromOrigin.x > CHUNK_WIDTH)
	{
		int x = chunkIndexOffsetX;
		chunkIndexOffsetX = (chunkIndexOffsetX + 1) % CHUNK_RENDER_DISTANCE;

		int swapEnd = utils::loopMod(x - 1, CHUNK_RENDER_DISTANCE);
		for (int z = 0; z < CHUNK_RENDER_DISTANCE; z++)
		{
			chunks[z][x].setPos(chunks[z][swapEnd].getPos() + glm::vec2(CHUNK_WIDTH, 0));

			chunks[z][x].generateBlocks();
			buildChunkMesh(x, z);
		}
		origin.x += CHUNK_WIDTH;
	}

	else if (-distanceFromOrigin.x > CHUNK_WIDTH)
	{
		int x = chunkIndexOffsetX;
		chunkIndexOffsetX = utils::loopMod(chunkIndexOffsetX - 1, CHUNK_RENDER_DISTANCE);

		int swapEnd = utils::loopMod(x - 1, CHUNK_RENDER_DISTANCE);
		for (int z = 0; z < CHUNK_RENDER_DISTANCE; z++)
		{
			chunks[z][swapEnd].setPos(chunks[z][x].getPos() - glm::vec2(CHUNK_WIDTH, 0));

			chunks[z][swapEnd].generateBlocks();
			buildChunkMesh(swapEnd, z);
		}
		origin.x -= CHUNK_WIDTH;
	}

	if (distanceFromOrigin.z > CHUNK_WIDTH)
	{
		int z = chunkIndexOffsetZ;
		chunkIndexOffsetZ = (chunkIndexOffsetZ + 1) % CHUNK_RENDER_DISTANCE;
		for (int x = 0; x < CHUNK_RENDER_DISTANCE; x++)
		{
			int swapEnd = utils::loopMod(z - 1, CHUNK_RENDER_DISTANCE);
			chunks[z][x].setPos(chunks[swapEnd][x].getPos() + glm::vec2(0, CHUNK_WIDTH));

			chunks[z][x].generateBlocks();
			buildChunkMesh(x, z);
		}
		origin.z += CHUNK_WIDTH;
	}

	else if (-distanceFromOrigin.z > CHUNK_WIDTH)
	{
		int z = chunkIndexOffsetZ;
		chunkIndexOffsetZ = utils::loopMod(chunkIndexOffsetZ - 1, CHUNK_RENDER_DISTANCE);

		int swapEnd = utils::loopMod(z - 1, CHUNK_RENDER_DISTANCE);
		for (int x = 0; x < CHUNK_RENDER_DISTANCE; x++)
		{
			chunks[swapEnd][x].setPos(chunks[z][x].getPos() - glm::vec2(0, CHUNK_WIDTH));

			chunks[swapEnd][x].generateBlocks();
			buildChunkMesh(x, swapEnd);
		}
		origin.z -= CHUNK_WIDTH;
	}

	std::cout << camera.getPos().x << ", " << camera.getPos().z << std::endl;
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
