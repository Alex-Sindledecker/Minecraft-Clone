#pragma once

#include "layers/Layer.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Settings.h"

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

private:
	Window m_window;
	std::vector<Layer*> m_layer_stack;

	pugi::xml_document m_doc;
	const char* m_settings_path;
	bool m_settings_changed = false;
};