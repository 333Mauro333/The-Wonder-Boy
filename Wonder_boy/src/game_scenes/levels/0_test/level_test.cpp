#include "level_test.h"

#include <iostream>

#include "game_manager/game_manager.h"

using std::cout;


namespace the_wonder_boy
{
	LevelTest::LevelTest(RenderWindow* window) : Scene(window)
	{
		cout << "Se ha creado un nivel de prueba.\n\n";

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
	void LevelTest::checkKeyPressedOnce(Keyboard::Key key)
	{
		player->keyPressedOnce(key);
	}
	void LevelTest::checkKeyReleased(Keyboard::Key key)
	{
		player->keyReleased(key);
	}

	void LevelTest::init()
	{
		// Se hacen conversiones de datos para evitar advertencias de Visual Studio.
		player = new Player(static_cast<float>(window->getSize().x / 2), static_cast<float>(window->getSize().y / 4.0f * 3.0f));

		float floorX = 0;
		float floorY = window->getSize().y / 4.0f * 3.5f;
		for (int i = 0; i < floorSize; i++)
		{
			floor[i] = new Floor(floorX, floorY);
			floorX += 64;
			if (i != 0 && i % 10 == 0)
			{
				floorY -= 100;
			}
		}

		view.setSize(Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
		view.setCenter(player->getPosition().x, player->getPosition().y - 100);
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
		const float distanceToCenter = static_cast<float>(window->getSize().x) / 10.0f;
		const float playerRightEdgePosition = player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x + player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f;
		const float playerLeftEdgePosition = player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f;


		if (playerRightEdgePosition > view.getCenter().x + distanceToCenter)
		{
			view.setCenter(playerRightEdgePosition - distanceToCenter, view.getCenter().y);
		}

		if (playerLeftEdgePosition < view.getCenter().x - view.getSize().x / 2.0f)
		{
			player->setPosition(Vector2f(view.getCenter().x - view.getSize().x / 2.0f + player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f, player->getPosition().y));
		}

		window->setView(view);
	}
}
