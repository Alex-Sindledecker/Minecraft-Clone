#include "pch.h"
#include "Game.h"

Game::Game(const char* settings_xml_path)
{
	m_settings_path = settings_xml_path;
	m_doc = Settings::load("res/Settings.xml");

	m_window.create(Settings::window_width, Settings::window_height, "Minecraft Clone", Settings::fullscreen);
}

Game::~Game()
{
	Settings::save(m_doc, m_settings_path);
}

Window* Game::getWindow()
{
	return &m_window;
}

void Game::init()
{
	for (int i = m_layer_stack.size() - 1; i >= 0; i--)
	{
		m_layer_stack[i]->setWindow(&m_window);
		m_layer_stack[i]->onCreate();
	}
}

void Game::run()
{
	float dt = 1 / 60.f;
	glClearColor(0.f, 0.1f, 0.3f, 1.f);
	while (m_window.closeButtonPressed() == false)
	{
		glfwSetTime(0);

		if (m_window.isKeyPressed(GLFW_KEY_ESCAPE))
			break;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 		for (int i = m_layer_stack.size() - 1; i >= 0; i--)
		{
			m_layer_stack[i]->onUpdate(dt);
			m_layer_stack[i]->onRender();
		}

		m_window.update();
		dt = glfwGetTime();
	}
}

void Game::pushLayer(Layer* layer)
{
	m_layer_stack.push_back(layer);
}

Layer* Game::popLayer()
{
	Layer* result = m_layer_stack[m_layer_stack.size() - 1];
	m_layer_stack.pop_back();

	return result;
}