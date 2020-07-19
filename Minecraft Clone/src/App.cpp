#include "pch.h"
#include "game/Game.h"

class TestLayer : public Layer
{
public:
	virtual void onUpdate(float dt) override
	{
		glm::vec2 middle = m_window->getSize() / glm::vec2(2);
		glm::vec2 delta_mouse_pos = m_window->getMousePos() - middle;
		m_window->setMousePos(middle);

		camera.lookVertically(delta_mouse_pos.y * sensitivity);
		camera.lookHorizontally(delta_mouse_pos.x * sensitivity);

		camera.computeDirectionVectors();
		if (m_window->isKeyPressed(GLFW_KEY_W))
			camera.move(camera.getViewDirection() * camera_speed * dt);
		if (m_window->isKeyPressed(GLFW_KEY_A))
			camera.move(camera.getRight() * -camera_speed * dt);
		if (m_window->isKeyPressed(GLFW_KEY_S))
			camera.move(-camera.getViewDirection() * camera_speed * dt);
		if (m_window->isKeyPressed(GLFW_KEY_D))
			camera.move(camera.getRight() * camera_speed * dt);
	
		std::string title = "X: " + std::to_string(camera.getPosition().x) + ", Y: " + std::to_string(camera.getPosition().y) + ", Z: " + std::to_string(camera.getPosition().z);
		m_window->setTitle((title + ", FPS: " + std::to_string(1 / dt)).c_str());
	}

	virtual void onRender() override
	{
		mainShader->use();
		mainShader->setUniformMatrix4("pv", camera.getViewProjectionTransform());
		myTexture->bind();
		vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		vao->unbind();
	}

	virtual void onCreate()
	{
		GLfloat verts[] = 
		{
			1, 1, 0,
			0, 1, 0,
			0, 0, 0,
			0, 0, 0,
			1, 0, 0,
			1, 1, 0
		};

		mainShader = ResourceManager::getShader("mainShader");
		myTexture = ResourceManager::getTexture2D("myTexture");
		vao = ResourceManager::getVertexArray("quadVAO");
		VertexBufferPtr vbo = ResourceManager::getVertexBuffer("quadVBO");
		vbo->init(verts, sizeof(verts));
		vao->bind();
		vao->push<float>(*vbo.get(), 3, 0);
		vao->unbind();

		mainShader->init("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
		myTexture->init("res/tex/atlas.png");

		glm::mat4 projection = glm::perspective(glm::radians(70.f), m_window->getSize().x / m_window->getSize().y, 0.1f, 100.f);
		glm::mat4 view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		camera = PerspectiveCamera(70.f, m_window->getSize().x / m_window->getSize().y, glm::vec3(16, 3, -11));
		camera.setViewRange(0.1, 32 * 16);

		sensitivity = 0.05, camera_speed = 10;
		m_window->setMousePos(m_window->getSize() / glm::vec2(2));
	}

private:
	ShaderPtr mainShader;
	Texture2DPtr myTexture;
	VertexArrayPtr vao;
	PerspectiveCamera camera;
	float sensitivity, camera_speed;
};

int main()
{
	Game game("res/Settings.xml");
	TestLayer layer;

	game.pushLayer(&layer);
	game.init();
	game.run();

	return 0;
}