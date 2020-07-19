#pragma once

#include "layers/Layer.h"
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
	void pushLayer(Layer* layer);
	Layer* popLayer();
	const GraphicsSettings& getGraphicsSettings() const;
	const GameSettings& getGameSettings() const;

private:
	void loadSettings(const char* xml_path);
	void saveSettings(const char* xml_path);

	Window m_window;
	std::vector<Layer*> m_layer_stack;

	GameSettings m_game_settings;
	GraphicsSettings m_graphics_settings;
	pugi::xml_document m_doc;
	const char* m_settings_path;
	bool m_settings_changed = false;
};