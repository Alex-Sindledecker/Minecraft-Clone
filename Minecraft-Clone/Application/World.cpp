#include "World.h"

#include "Application.h"

World& World::get()
{
	static World world;
	return world;
}

void World::update(float dt)
{
	camera.update(dt);
	camera.updateView();
}

void World::render()
{
	static gl::ShaderProgram shaderProgram = 0;
	static gl::VertexArray vao = 0;

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

		camera.updateProjection();
		camera.updateView();
	}

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvp"), 1, GL_FALSE, &camera.getViewProjection()[0][0]);
	gl::drawElements(vao, 6);
}
