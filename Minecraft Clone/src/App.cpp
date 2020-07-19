#include "pch.h"
#include "game/Game.h"

#include <thread>

int main()
{
	Game game("res/Settings.xml");

	game.init();
	game.run();

	return 0;
}