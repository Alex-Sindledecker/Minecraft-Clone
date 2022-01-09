#pragma once

#include "World.h"

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
	float getWindowWidth();
	float getWindowHeight();
	float getAspectRatio();
	GLFWwindow* getWindow();

	Application(Application const&) = delete;
	void operator=(Application const&) = delete;

private:
	Application() : world(World::get()) {}
	~Application() {}

	void mainMenuProc(float dt);
	void worldSelectProc(float dt);
	void worldCreateProc(float dt);
	void loadingProc(float dt);
	void activeProc(float dt);
	void pausedProc(float dt);

	World& world;

	GLFWwindow* window;
	float windowWidth, windowHeight;

	GameState gameState;
};