#include "pch.h"
#include "game/Game.h"
#include "layers/SkyboxLayer.h"
#include "layers/WaterLayer.h"

int main()
{
	SkyboxLayer skybox_layer;
	WaterLayer water_layer;

	Game game("res/Settings.xml");

	game.pushLayer(&skybox_layer);
	game.pushLayer(&water_layer);

	game.init();
	game.run();

	return 0;
}