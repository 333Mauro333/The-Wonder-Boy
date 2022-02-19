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
	void LevelTest::update()
	{
		player->update(GameManager::getDeltaTime());

		updateCamera();

		hud->update();

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
		window->draw(background);
		player->draw(window);
		for (int i = 0; i < floorSize; i++)
		{
			floor[i]->draw(window);
		}
		hud->draw(window);
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
		background.setSize(static_cast<Vector2f>(window->getSize()));
		background.setFillColor(sf::Color(128, 128, 255)); // Celeste
		background.setOrigin(background.getGlobalBounds().width / 2.0f, background.getGlobalBounds().height / 2.0f);

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
		view.setCenter(player->getPosition().x, player->getPosition().y - window->getSize().y / 8.0f);
		window->setView(view);

		hud = new HUD(window, player);
	}
	void LevelTest::destroy()
	{
		delete player;
		delete hud;

		for (int i = 0; i < floorSize; i++)
		{
			delete floor[i];
		}

	}

	void LevelTest::moveCameraInY(float start, float end, float pixelsToMove)
	{
		if (player->getPosition().x >= start && player->getPosition().x <= end)
		{
			float distanceTrayectory = end - start; // Distancia total de principio a fin.

			// Movimiento total / distancia entre la que se va a mover * velocidad del jugador en cada frame.
			view.setCenter(view.getCenter().x, view.getCenter().y + pixelsToMove / distanceTrayectory * player->getSpeed() * GameManager::getDeltaTime());
		}
	}
	void LevelTest::updateCamera()
	{
		const float distanceToCenter = static_cast<float>(window->getSize().x) / 10.0f;
		const float playerRightEdgePosition = player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x + player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f;
		const float playerLeftEdgePosition = player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f;


		// Si el jugador avanza lo suficiente hacia la derecha...
		if (playerRightEdgePosition + distanceToCenter > view.getCenter().x)
		{
			moveCameraInY(1500.0f, 2000.0f, 500.0f);
			moveCameraInY(2500.0f, 4000.0f, -500.0f);
			moveCameraInY(4500.0f, 4600.0f, 200.0f);
			moveCameraInY(4700.0f, 5000.0f, -200.0f);

			// ...lo sigue la cámara.
			view.setCenter(playerRightEdgePosition + distanceToCenter, view.getCenter().y);
		}

		// Si el jugador choca contra el límite izquierdo de la pantalla...
		if (playerLeftEdgePosition < view.getCenter().x - view.getSize().x / 2.0f)
		{
			// ...no puede retroceder más.
			player->setPosition(Vector2f(view.getCenter().x - view.getSize().x / 2.0f + player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f, player->getPosition().y));
			player->stopWalkSpeed();
		}

		if (player->getPosition().y > view.getCenter().y + view.getSize().y / 1.5f)
		{
			player->setLost(true);
			cout << "Perdio\n";
		}

		background.setPosition(view.getCenter());

		window->setView(view); // Se le pasa a la ventana la view actualizada.
	}
}
