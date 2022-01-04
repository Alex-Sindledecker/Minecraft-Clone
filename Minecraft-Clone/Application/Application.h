#pragma once

#include "../gl.h"
#include <GLFW/glfw3.h>

enum class GameState
{
	MainMenu,
	WorldSelect,
	WorldCreate,
	Loading,
	Active, //Playing game
	Paused
};

class Application
{
public:

	static Application& get();

	int init();
	void run();
	void deinit();

	Application(Application const&) = delete;
	void operator=(Application const&) = delete;

private:
	Application() {}
	~Application() {}

	void mainMenuProc(float dt);
	void worldSelectProc(float dt);
	void worldCreateProc(float dt);
	void loadingProc(float dt);
	void activeProc(float dt);
	void pausedProc(float dt);

	GLFWwindow* window;
	float windowWidth, windowHeight;
};