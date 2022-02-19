#include "level_test.h"

#include <iostream>

#include "game_manager/game_manager.h"
#include "game_controls/game_controls.h"
#include "scene_manager/scene_manager.h"
#include "game_scenes/screens/main_menu/main_menu.h"

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

	// Funciones públicas.
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

		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::screenReturn)))
		{
			view.setCenter(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
			
			window->setView(view);
			SceneManager::loadNewScene(new MainMenu(window, SELECTED_OPTION::PLAY));
		}
	}
	void LevelTest::checkKeyReleased(Keyboard::Key key)
	{
		player->keyReleased(key);
	}


	// Funciones privadas.
	void LevelTest::init()
	{
		// Se hacen conversiones de datos para evitar advertencias de Visual Studio.
		player = new Player(static_cast<float>(window->getSize().x / 2), static_cast<float>(window->getSize().y / 4.0f * 3.0f));

		float floorX = 0;
		float floorY = window->getSize().y / 4.0f * 3.5f;
		for (int i = 0; i < floorSize; i++)
		{
			if (i == 8 || i == 10)
			{
				floor[i] = new Floor(floorX, floorY, FLOOR_TYPE::END);
				floorX += floor[i]->getBoxCollision().getGlobalBounds().width * 2;
			}
			else if (i == 9 || i == 11)
			{
				floor[i] = new Floor(floorX, floorY, FLOOR_TYPE::START);
			}
			else
			{
				floor[i] = new Floor(floorX, floorY, FLOOR_TYPE::NORMAL);
			}

			floorX += floor[i]->getBoxCollision().getGlobalBounds().width;
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


		// Si el jugador avanza lo suficiente hacia la derecha...
		if (playerRightEdgePosition > view.getCenter().x + distanceToCenter)
		{
			// ...lo sigue la cámara.
			view.setCenter(playerRightEdgePosition - distanceToCenter, view.getCenter().y);
		}

		// Si el jugador choca contra el límite izquierdo de la pantalla...
		if (playerLeftEdgePosition < view.getCenter().x - view.getSize().x / 2.0f)
		{
			// ...no retrocede más.
			player->setPosition(Vector2f(view.getCenter().x - view.getSize().x / 2.0f + player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f, player->getPosition().y));
		}

		window->setView(view); // Se le pasa a la ventana la view actualizada.
	}
}
