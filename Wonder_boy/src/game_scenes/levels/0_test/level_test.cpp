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

		init();
	}
	LevelTest::~LevelTest()
	{
		destroy();

		cout << "El nivel de prueba ha sido eliminado de la memoria.\n";
	}

	void LevelTest::update(float deltaTime)
	{
		player->update(deltaTime);

		updateCamera();

		for (int i = 0; i < floorSize; i++)
		{
			if (player->isCollidingWith(floor[i]))
			{
				player->collisionWith(floor[i]);
			}
		}
	}
	void LevelTest::draw()
	{
		player->draw(window);
		for (int i = 0; i < floorSize; i++)
		{
			floor[i]->draw(window);
		}
	}

	void LevelTest::init()
	{
		// Se hacen conversiones de datos para evitar advertencias de Visual Studio.
		player = new Player(static_cast<float>(GameManager::getWindowSize().x / 2), static_cast<float>(GameManager::getWindowSize().y / 4 * 3));

		int aux = 0;
		for (int i = 0; i < floorSize; i++)
		{
			floor[i] = new Floor(aux, window->getSize().y / 4.0f * 3.5f);
			aux += 64;
		}

		view.setSize(window->getSize().x, window->getSize().y);
		view.setCenter(player->getRenderer().getPosition().x, player->getRenderer().getPosition().y - 100);
		window->setView(view);
	}
	void LevelTest::destroy()
	{
		delete player;

		for (int i = 0; i < floorSize; i++)
		{
			delete floor[i];
		}
	}
	void LevelTest::updateCamera()
	{
		const int distanceToCenter = window->getSize().x / 10;


		if (player->getRenderer().getPosition().x > view.getCenter().x + distanceToCenter)
		{
			view.setCenter(player->getRenderer().getPosition().x - distanceToCenter, view.getCenter().y);
		}

		if (player->getRenderer().getPosition().x < view.getCenter().x - view.getSize().x / 2.0f)
		{
			player->setPosition(Vector2f(view.getCenter().x - view.getSize().x / 2.0f, player->getRenderer().getPosition().y));
		}

		window->setView(view);
	}
}
