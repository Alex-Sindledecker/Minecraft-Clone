#include "Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Application& Application::get()
{
	static Application app;

	app.windowWidth = 800;
	app.windowHeight = 600;

	return app;
}

int Application::init()
{
	//GLFW initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Window initialization
	window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//OpenGL initialization
	gl::init((GLADloadproc)glfwGetProcAddress);
}

void Application::run()
{
	gameState = GameState::Active;

	float dt = 1.f / 60.f;

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Game state switch
		switch (gameState)
		{
		case GameState::MainMenu:
			mainMenuProc(dt);
			break;
		case GameState::WorldSelect:
			worldSelectProc(dt);
			break;
		case GameState::WorldCreate:
			worldCreateProc(dt);
			break;
		case GameState::Loading:
			loadingProc(dt);
			break;
		case GameState::Active:
			activeProc(dt);
			break;
		case GameState::Paused:
			pausedProc(dt);
			break;
		}

		//Update window and check for events
		glfwSwapBuffers(window);
		glfwPollEvents();

		dt = glfwGetTime();
		glfwSetTime(0);
	}
}

void Application::deinit()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

float Application::getWindowWidth()
{
	return windowWidth;
}

float Application::getWindowHeight()
{
	return windowHeight;
}

float Application::getAspectRatio()
{
	return windowWidth / windowHeight;
}

GLFWwindow* Application::getWindow()
{
	return window;
}

void Application::mainMenuProc(float dt)
{
}

void Application::worldSelectProc(float dt)
{
}

void Application::worldCreateProc(float dt)
{
}

void Application::loadingProc(float dt)
{
}

void Application::activeProc(float dt)
{
	world.update(dt);
	world.render();
}

void Application::pausedProc(float dt)
{
	world.render();

	//pause screen
}
