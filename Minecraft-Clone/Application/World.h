#pragma once

#include "../gl.h"
#include <GLFW/glfw3.h>

#include "../Cameras/FpsCamera.h"

class World
{
public:
	static World& get();

	void update(float dt);
	void render();

	World(World const&) = delete;
	void operator=(World const&) = delete;

private:
	World() {}
	~World() {}

	FpsCamera camera;
};