#include "pch.h"
#include "Game.h"

ShaderPtr mainShader;
Texture2DPtr myTexture;
VertexArrayPtr vao;
PerspectiveCamera camera;
float dt, sensitivity, camera_speed;

Game::Game(const char* settings_xml_path)
{
	m_settings_path = settings_xml_path;
	loadSettings(settings_xml_path);

	m_window.create(m_graphics_settings.window_width, m_graphics_settings.window_height, "Minecraft Clone", m_graphics_settings.fullscreen);
}

Game::~Game()
{
	if (m_settings_changed)
		saveSettings(m_settings_path);
}

Window* Game::getWindow()
{
	return &m_window;
}

void Game::init()
{
	GLfloat verts[] = {
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

	glm::mat4 projection = glm::perspective(glm::radians(70.f), m_window.getSize().x / m_window.getSize().y, 0.1f, 100.f);
	glm::mat4 view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	camera = PerspectiveCamera(70.f, m_window.getSize().x / m_window.getSize().y, glm::vec3(16, 3, -11));
	camera.setViewRange(0.1, 32 * 16);

	dt = 0, sensitivity = 0.05, camera_speed = 10;
	m_window.setMousePos(m_window.getSize() / glm::vec2(2));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Game::run()
{
	glClearColor(0.f, 0.1f, 0.3f, 1.f);
	while (m_window.closeButtonPressed() == false)
	{
		glfwSetTime(0);
		glm::vec2 middle = m_window.getSize() / glm::vec2(2);
		glm::vec2 delta_mouse_pos = m_window.getMousePos() - middle;
		m_window.setMousePos(middle);

		camera.lookVertically(delta_mouse_pos.y * sensitivity);
		camera.lookHorizontally(delta_mouse_pos.x * sensitivity);

		camera.computeDirectionVectors();
		if (m_window.isKeyPressed(GLFW_KEY_W))
			camera.move(camera.getViewDirection() * camera_speed * dt);
		if (m_window.isKeyPressed(GLFW_KEY_A))
			camera.move(camera.getRight() * -camera_speed * dt);
		if (m_window.isKeyPressed(GLFW_KEY_S))
			camera.move(-camera.getViewDirection() * camera_speed * dt);
		if (m_window.isKeyPressed(GLFW_KEY_D))
			camera.move(camera.getRight() * camera_speed * dt);
		if (m_window.isKeyPressed(GLFW_KEY_ESCAPE))
			break;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::string title = "X: " + std::to_string(camera.getPosition().x) + ", Y: " + std::to_string(camera.getPosition().y) + ", Z: " + std::to_string(camera.getPosition().z);
		m_window.setTitle((title + ", FPS: " + std::to_string(1 / dt)).c_str());

		mainShader->use();
		mainShader->setUniformMatrix4("pv", camera.getViewProjectionTransform());
		myTexture->bind();
		vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		vao->unbind();

		m_window.update();
		dt = glfwGetTime();
	}
}

void Game::loadSettings(const char* xml_path)
{
	pugi::xml_parse_result result = m_doc.load_file(xml_path);
	if (!result)
	{
		CONSOLE_LOG_ERROR("Game.cpp", result.description());
		return;
	}

	pugi::xml_node root = m_doc.child("Settings");
	pugi::xml_node gameplay = root.child("GameplaySettings");
	pugi::xml_node graphics = root.child("GraphicsSettings");

	m_game_settings.render_distance = graphics.child("RenderDistance").attribute("value").as_int();

	m_graphics_settings.window_width = graphics.child("WindowSize").attribute("width").as_int();
	m_graphics_settings.window_height = graphics.child("WindowSize").attribute("height").as_int();
	m_graphics_settings.fullscreen = graphics.child("WindowSize").attribute("fullscreen").as_bool();
}

void Game::saveSettings(const char* xml_path)
{
	m_doc.save_file(xml_path);
}
