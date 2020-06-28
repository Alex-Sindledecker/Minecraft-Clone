#include "pch.h"
#include "Window.h"

int main()
{
	Window window(1280, 720, "Minecraft 2");

	glClearColor(0.12f, 0.3f, 0.78f, 1.f);
	while (window.closeButtonPressed() == false)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		window.update();
	}

	return 0;
}