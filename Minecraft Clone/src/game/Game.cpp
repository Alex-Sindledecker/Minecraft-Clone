#include "pch.h"
#include "Game.h"

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
	for (Layer* layer : m_layer_stack)
	{
		layer->setWindow(&m_window);
		layer->onCreate();
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

const GraphicsSettings& Game::getGraphicsSettings() const
{
	return m_graphics_settings;
}

const GameSettings& Game::getGameSettings() const
{
	return m_game_settings;
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
