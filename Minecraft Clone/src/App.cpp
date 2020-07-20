#include "pch.h"
#include "game/Game.h"
#include "layers/SkyboxLayer.h"

int main()
{
	SkyboxLayer skybox_layer;

	Game game("res/Settings.xml");

	game.pushLayer(&skybox_layer);
	game.init();
	game.run();

	return 0;
}