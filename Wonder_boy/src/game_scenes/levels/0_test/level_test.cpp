#include "level_test.h"

#include <iostream>

#include "game_manager/game_manager.h"

using std::cout;


namespace the_wonder_boy
{
	LevelTest::LevelTest(RenderWindow* window) : Scene()
	{
		cout << "Se ha creado un nivel de prueba.\n\n";

		this->window = window;
		player = new Player(static_cast<float>(GameManager::getWindowSize().x / 2), static_cast<float>(GameManager::getWindowSize().y / 4 * 3));
	}
	LevelTest::~LevelTest()
	{
		destroy();

		cout << "El nivel de prueba ha sido eliminado de la memoria.\n";
	}

	void LevelTest::init()
	{

	}
	void LevelTest::update(float deltaTime)
	{

	}
	void LevelTest::draw()
	{
		player->draw(window);
	}

	void LevelTest::destroy()
	{
		delete player;
	}
}
