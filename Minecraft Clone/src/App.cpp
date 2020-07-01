#include "pch.h"
#include "ResourceManager.h"
#include "Chunk.h"
#include "Window.h"
#include "Camera.h"

#include <thread>

void drawAThing()
{
	static GLfloat vertices[] = {
		1.f, 1.f,
		0.f, 1.f,
		0.f, 0.f,

		0.f, 0.f,
		1.f, 0.f,
		1.f, 1.f
	};
	static GLuint vao = 0, vbo;
	if (vao == 0)
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindVertexArray(vao);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

int main()
{
	Window window(1280, 720, "Minecraft 2");

	ShaderPtr mainShader = ResourceManager::getShader("mainShader");
	Texture2DPtr myTexture = ResourceManager::getTexture2D("myTexture");

	mainShader->init("res/shaders/block_vertex.glsl", "res/shaders/block_fragment.glsl");
	myTexture->init("res/tex/sample.png");

	glm::mat4 projection = glm::perspective(glm::radians(70.f), window.getSize().x / window.getSize().y, 0.1f, 100.f);
	glm::mat4 view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	Terrain terrain(NULL, 16);
	Block block;
	block.id = BLOCK_ID_GRASS;
	terrain.setBlock(block, 10, 13, 10);
	Chunk chunk(&terrain, glm::vec3(0, 0, 0));
	chunk.build();
	PerspectiveCamera camera(70.f, window.getSize().x / window.getSize().y, glm::vec3(0, 0, 0));

	float dt = 0, sensitivity = 0.05, camera_speed = 10;
	window.setMousePos(window.getSize() / glm::vec2(2));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glClearColor(0.f, 0.1f, 0.3f, 1.f);
	while (window.closeButtonPressed() == false)
	{
		glfwSetTime(0);
		glm::vec2 middle = window.getSize() / glm::vec2(2);
		glm::vec2 delta_mouse_pos = window.getMousePos() - middle;
		window.setMousePos(middle);

		camera.lookVertically(delta_mouse_pos.y * sensitivity);
		camera.lookHorizontally(delta_mouse_pos.x * sensitivity);
		
		camera.computeDirectionVectors();
		if (window.isKeyPressed(GLFW_KEY_W))
			camera.move(camera.getViewDirection() * camera_speed * dt);
		if (window.isKeyPressed(GLFW_KEY_A))
			camera.move(camera.getRight() * -camera_speed * dt);
		if (window.isKeyPressed(GLFW_KEY_S))
			camera.move(-camera.getViewDirection() * camera_speed * dt);
		if (window.isKeyPressed(GLFW_KEY_D))
			camera.move(camera.getRight() * camera_speed * dt);
		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			break;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::string title = "X: " + std::to_string(camera.getPosition().x) + ", Y: " + std::to_string(camera.getPosition().y) + ", Z: " + std::to_string(camera.getPosition().z);
		window.setTitle(title.c_str());

		mainShader->use();
		mainShader->setUniformMatrix4("pv", camera.getViewProjectionTransform());
		myTexture->bind();
		chunk.t_render();

		window.update();
		dt = glfwGetTime();
	}

	return 0;
}