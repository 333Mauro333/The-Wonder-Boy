#include "level_test.h"

#include <iostream>

#include "game_manager/game_manager.h"
#include "game_controls/game_controls.h"
#include "scene_manager/scene_manager.h"
#include "game_scenes/screens/main_menu/main_menu.h"
#include "collision_manager/collision_manager.h"
#include "enemies/snail/snail.h"
#include "enemies/wasp/wasp.h"

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
			for (int j = 0; j < Player::getStoneHammersSize(); j++)
			{
				if (CollisionManager::isColliding(player->getPlayerStoneHammer(j), floor[i]))
				{
					player->getPlayerStoneHammer(j)->hit();
				}
			}

			if (CollisionManager::isColliding(player, floor[i]))
			{
				player->collisionWith(floor[i]);
			}
		}
		for (int i = 0; i < fruitSize; i++)
		{
			fruit[i]->update(GameManager::getDeltaTime());

			if (CollisionManager::isColliding(player, fruit[i]))
			{
				fruit[i]->take();
				player->addHealth(fruit[i]->getHealthValue());
				player->addPoints(fruit[i]->getPointsValue());
				cout << "La fruta " << i + 1 << " fue agarrada.\n";
			}
		}
		for (int i = 0; i < stoneSize; i++)
		{
			if (CollisionManager::isColliding(player, stone[i]) && !player->getHit())
			{
				player->tripOn(stone[i]);
				cout << "Esta tocando la piedra " << i + 1 << ".\n";
			}
		}
		for (int i = 0; i < bonfireSize; i++)
		{
			bonfire[i]->update(GameManager::getDeltaTime());

			if (CollisionManager::isColliding(player, bonfire[i]))
			{
				player->lose(LOSING_TYPE::BURNED);
				cout << "Se quemo con la fogata  " << i + 1 << ".\n";
			}
		}
		for (int i = 0; i < enemySize; i++)
		{
			enemy[i]->update(GameManager::getDeltaTime());

			if (CollisionManager::isColliding(player, enemy[i]))
			{
				player->lose(LOSING_TYPE::NORMAL);
			}

			for (int j = 0; j < Player::getStoneHammersSize(); j++)
			{
				if (CollisionManager::isColliding(player->getPlayerStoneHammer(j), enemy[i]))
				{
					enemy[i]->defeat();
					player->getPlayerStoneHammer(j)->hit();
					cout << "El enemigo pierde.\n";
				}
			}
		}
	}
	void LevelTest::draw()
	{
		window->draw(background);
		for (int i = 0; i < signSize; i++)
		{
			sign[i]->draw(window);
		}
		for (int i = 0; i < floorSize; i++)
		{
			floor[i]->draw(window);
		}
		player->draw(window);
		for (int i = 0; i < fruitSize; i++)
		{
			fruit[i]->draw(window);
		}
		for (int i = 0; i < enemySize; i++)
		{
			enemy[i]->draw(window);
		}
		for (int i = 0; i < stoneSize; i++)
		{
			stone[i]->draw(window);
		}
		for (int i = 0; i < bonfireSize; i++)
		{
			bonfire[i]->draw(window);
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
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(Keyboard::C)))
		{
			resetLevel();
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
		background.setFillColor(sf::Color(128, 128, 255)); // Celeste.
		background.setOrigin(background.getGlobalBounds().width / 2.0f, background.getGlobalBounds().height / 2.0f);


		// Pisos.
		float x = 0.0f;
		float y = window->getSize().y / 4.0f * 3.5f;
		for (int i = 0; i < floorSize; i++)
		{
			if (i == 8 || i == 10)
			{
				floor[i] = new Floor(x, y, FLOOR_TYPE::END);
				x -= floor[i - 1]->getBoxCollision().getGlobalBounds().width;
				x += floor[i]->getBoxCollision().getGlobalBounds().width;
				floor[i]->setPosition(x, y);
				x += floor[i]->getBoxCollision().getGlobalBounds().width * 2;
			}
			else if (i == 9 || i == 11)
			{
				floor[i] = new Floor(x, y, FLOOR_TYPE::START);
			}
			else
			{
				floor[i] = new Floor(x, y, FLOOR_TYPE::NORMAL);
			}

			x += floor[i]->getBoxCollision().getGlobalBounds().width;
		}

		// Señales.
		x = floor[1]->getInitialPosition().x;
		y = floor[1]->getInitialPosition().y;
		sign[0] = new Sign(x, y, SIGN_TYPE::FIRST);
		sign[1] = new Sign(x + 2000.0f, y, SIGN_TYPE::SECOND);
		sign[2] = new Sign(x + 4000.0f, y, SIGN_TYPE::THIRD);
		sign[3] = new Sign(x + 6000.0f, y, SIGN_TYPE::FOURTH);
		sign[4] = new Sign(x + 8000.0f, y, SIGN_TYPE::GOAL);

		// Frutas.
		x = floor[3]->getInitialPosition().x;
		y = floor[3]->getInitialPosition().y - 200.0f;
		for (int i = 0; i < fruitSize; i++)
		{
			if (i < 3)
			{
				fruit[i] = new Fruit(x, y, FRUIT_TYPE::APPLE);
			}
			else if (i < 6)
			{
				fruit[i] = new Fruit(x, y, FRUIT_TYPE::BANANAS);
			}
			else if (i < 9)
			{
				fruit[i] = new Fruit(x, y, FRUIT_TYPE::CARROT);
			}
			else
			{
				fruit[i] = new Fruit(x, y, FRUIT_TYPE::TOMATO);
			}

			x += floor[i + 3]->getBoxCollision().getGlobalBounds().width;
		}

		// Piedras.
		x = 1000.0f;
		y = window->getSize().y / 4.0f * 3.5f;
		for (int i = 0; i < stoneSize; i++)
		{
			stone[i] = new Stone(x, y);

			x += 500.0f;
		}

		// Fogatas.
		x = floor[15]->getInitialPosition().x;
		y = floor[15]->getInitialPosition().y;
		for (int i = 0; i < bonfireSize; i++)
		{
			bonfire[i] = new Bonfire(x, y);
			x += floor[15]->getBoxCollision().getGlobalBounds().width * 2.0f;
		}

		// Enemigos.
		x = floor[20]->getInitialPosition().x;
		y = floor[20]->getInitialPosition().y;
		for (int i = 0; i < enemySize; i++)
		{
			if (i % 3 == 0)
			{
				enemy[i] = new Snail(x, y);
			}
			else
			{
				enemy[i] = new Wasp(x, y, WASP_VERTICAL_SPEED::FAST);
			}

			x += 100.0f;
		}

		// Jugador.
		player = new Player(sign[0]->getRenderer().getPosition().x, sign[0]->getRenderer().getPosition().y);
		player->setNecessaryDistanceToWin(sign[4]->getRenderer().getPosition().x + sign[4]->getRenderer().getGlobalBounds().width);

		view.setSize(Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
		view.setCenter(player->getPosition().x, player->getPosition().y - window->getSize().y / 4.0f);
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
		for (int i = 0; i < signSize; i++)
		{
			delete sign[i];
		}
		for (int i = 0; i < fruitSize; i++)
		{
			delete fruit[i];
		}
		for (int i = 0; i < stoneSize; i++)
		{
			delete stone[i];
		}
		for (int i = 0; i < bonfireSize; i++)
		{
			delete bonfire[i];
		}
		for (int i = 0; i < enemySize; i++)
		{
			delete enemy[i];
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
			//moveCameraInY(1500.0f, 2000.0f, 500.0f);
			//moveCameraInY(2500.0f, 4000.0f, -500.0f);
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
			player->lose(LOSING_TYPE::NORMAL);
		}

		for (int i = 0; i < Player::getStoneHammersSize(); i++)
		{
			if (player->getPlayerStoneHammer(i)->getIsThrown() && player->getPlayerStoneHammer(i)->getPosition().y > view.getCenter().y + view.getSize().y / 1.5f)
			{
				player->getPlayerStoneHammer(i)->hit();
			}
		}
		for (int i = 0; i < enemySize; i++)
		{
			float distanceToBeActivated = view.getSize().x;

			if (!enemy[i]->isActive() && !enemy[i]->isDefeated() && player->getPosition().x + distanceToBeActivated > enemy[i]->getPosition().x)
			{
				if (!reseted)
				{
					enemy[i]->activate();
					cout << "Se ha activado el enemigo " << i + 1 << ".\n";
				}
				else
				{
					if (player->getPosition().x + distanceToBeActivated / 1.5f < enemy[i]->getPosition().x)
					{
						enemy[i]->activate();
						cout << "Se ha activado el enemigo " << i + 1 << ".\n";
					}
				}
			}
			else if (enemy[i]->isDefeated() && enemy[i]->isActive() && enemy[i]->getPosition().y > view.getCenter().y + view.getSize().y / 1.5f)
			{
				enemy[i]->deactivate();
				cout << "El enemigo " << i + 1 << " fue desactivado.\n";
			}
		}
		for (int i = 0; i < fruitSize; i++)
		{
			float distanceToBeActivated = view.getSize().x / 3.0f;

			if (!fruit[i]->isActive() && !fruit[i]->wasTaken() && player->getPosition().x + distanceToBeActivated > fruit[i]->getPosition().x)
			{
				if (!reseted)
				{
					fruit[i]->activate();
				}
				else
				{
					if (player->getPosition().x + distanceToBeActivated / 1.5f < fruit[i]->getPosition().x)
					{
						fruit[i]->activate();
						cout << "Se ha activado la fruta " << i + 1 << ".\n";
					}
				}
				cout << "Se ha activado la fruta " << i + 1 << ".\n";
			}
		}

		background.setPosition(view.getCenter());

		window->setView(view); // Se le pasa a la ventana la view actualizada.
	}

	Vector2f LevelTest::getPlayerCheckpointPosition()
	{
		int checkPointNumber = 0;

		for (int i = 0; i < signSize; i++)
		{
			if (player->getPosition().x < sign[i]->getRenderer().getPosition().x - sign[i]->getRenderer().getGlobalBounds().width)
			{
				checkPointNumber = (i - 1 <= 0) ? 0 : i - 1;
				break;
			}
		}

		return sign[checkPointNumber]->getRenderer().getPosition();
	}

	void LevelTest::resetLevel()
	{
		reseted = true;

		player->reset();
		player->setPosition(getPlayerCheckpointPosition());

		for (int i = 0; i < enemySize; i++)
		{
			enemy[i]->reset();
		}
		for (int i = 0; i < fruitSize; i++)
		{
			fruit[i]->reset();
		}

		view.setCenter(player->getPosition().x, player->getPosition().y - window->getSize().y / 4.0f);
		window->setView(view);
	}
}
