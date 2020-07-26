#include "pch.h"
#include "game/Game.h"
#include "layers/SkyboxLayer.h"
#include "layers/NoiseTestingLayer.h"
#include "world/terrain/TerrainGenerator.h"

int main()
{
	SkyboxLayer skybox_layer;
	NoiseTestingLayer layer;

	Game game("res/Settings.xml");

	game.pushLayer(&skybox_layer);
	game.pushLayer(&layer);
	game.init();
	game.run();

	return 0;
}