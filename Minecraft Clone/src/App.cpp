#include "pch.h"
#include "chunk/Chunk.h"
#include "game/Camera.h"
#include "ResourceManager.h"
#include "toolbox.h"
#include "Window.h"

#include <thread>

int main()
{
	Window window(1920, 1080, "Minecraft 2");

	ShaderPtr mainShader = ResourceManager::getShader("mainShader");
	Texture2DPtr myTexture = ResourceManager::getTexture2D("myTexture");

	mainShader->init("res/shaders/block_vertex.glsl", "res/shaders/block_fragment.glsl");
	myTexture->init("res/tex/atlas.png");

	glm::mat4 projection = glm::perspective(glm::radians(70.f), window.getSize().x / window.getSize().y, 0.1f, 100.f);
	glm::mat4 view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	Terrain terrain;

	Chunk* chunks = new Chunk[32 * 32 * 16];
	int index = 0;
	for (int i = 0; i < 16; i++)
	{
		for (int n = -16; n < 16; n++)
		{
			for (int k = -16; k < 16; k++)
			{
				chunks[index].setPosition(glm::vec3(k * 16, i * 16, n * 16));
				chunks[index].setTerrain(&terrain);
				chunks[index].build();
				index++;
			}
		}
	}

	PerspectiveCamera camera(70.f, window.getSize().x / window.getSize().y, glm::vec3(16, 3, -11));
	camera.setViewRange(0.1, 32 * 16);

	float dt = 0, sensitivity = 0.05, camera_speed = 10;
	window.setMousePos(window.getSize() / glm::vec2(2));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
		window.setTitle((title + ", FPS: " + std::to_string(1 / dt)).c_str());

		mainShader->use();
		mainShader->setUniformMatrix4("pv", camera.getViewProjectionTransform());
		myTexture->bind();
		index = 0;
		for (int i = 0; i < 32 * 32 * 16; i++)
		{
			mainShader->setUniformVector3("chunk_pos", chunks[i].getPosition());
			chunks[i].t_render();
		}

		window.update();
		dt = glfwGetTime();
	}

	return 0;
}