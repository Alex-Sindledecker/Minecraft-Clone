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
	GameState gameState = GameState::Active;

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
	}
}

void Application::deinit()
{
	glfwDestroyWindow(window);
	glfwTerminate();
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
	static gl::ShaderProgram shaderProgram = 0;
	static gl::VertexArray vao = 0;
	static glm::mat4 mvp = glm::identity<glm::mat4>();

	if (shaderProgram == 0)
	{
		shaderProgram = gl::loadShader("Shaders/testVertex.glsl", "Shaders/testFragment.glsl");

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, // left  
			 0.5f, -0.5f, 0.0f, // right 
			 0.5f,  0.5f, 0.0f,  // top
			 -0.5f, 0.5f, 0.f
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};

		gl::Buffer VBO = gl::createBuffer(GL_ARRAY_BUFFER, vertices, sizeof(vertices), GL_STATIC_DRAW);
		gl::Buffer EBO = gl::createBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices), GL_STATIC_DRAW);

		std::vector<gl::VertexAttribute> attributes = {
			{
				(void*)0,
				3,
				0,
				VBO,
				3 * sizeof(float),
				GL_FLOAT,
				GL_ARRAY_BUFFER
			}
		};

		vao = gl::createVertexArray(attributes, EBO);

		mvp = glm::perspective(glm::radians(45.f), (float)windowWidth / (float)windowHeight, 0.1f, 100.f) *
			glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvp"), 1, GL_FALSE, &mvp[0][0]);
	gl::drawElements(vao, 6);
}

void Application::pausedProc(float dt)
{
}
