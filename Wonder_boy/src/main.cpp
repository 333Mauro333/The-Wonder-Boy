#include "game_manager/game_manager.h"

using the_wonder_boy::GameManager;


int main()
{
	GameManager* gameManager = new GameManager(800, 600, "The Wonder Boy");

	gameManager->run();

	delete gameManager;


	return 0;
}