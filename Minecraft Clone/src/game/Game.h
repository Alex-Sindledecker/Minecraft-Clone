#pragma once

#include "Camera.h"
#include "ResourceManager.h"
#include "Window.h"
#include "pugixml.hpp"

struct GameSettings
{
	unsigned int render_distance;
};

struct GraphicsSettings
{
	GLuint gl_version_major;
	GLuint gl_version_minor;
	unsigned int window_width;
	unsigned int window_height;
	unsigned int antiailising_level;
	unsigned int anisotropic_filtering_level;
	bool fullscreen;
};

class Game
{
public:
	Game(const char* settings_xml_path);
	~Game();

	Window* getWindow();
	void init();
	void run();

private:
	void loadSettings(const char* xml_path);
	void saveSettings(const char* xml_path);

	GameSettings m_game_settings;
	GraphicsSettings m_graphics_settings;
	Window m_window;
	pugi::xml_document m_doc;
	const char* m_settings_path;
	bool m_settings_changed = false;
};