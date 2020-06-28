#include "pch.h"
#include "ResourceManager.h"
#include "Window.h"

int main()
{
	Window window(1280, 720, "Minecraft 2");

	ResourceManager::getShader("mainShader")->init("res/shaders/block_vertex.glsl", "res/shaders/block_fragment.glsl");
	ResourceManager::getTexture2D("myTexture")->init("res/tex/sample.png");

	glClearColor(0.12f, 0.23f, 0.68f, 1.f);
	while (window.closeButtonPressed() == false)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		window.update();
	}

	return 0;
}