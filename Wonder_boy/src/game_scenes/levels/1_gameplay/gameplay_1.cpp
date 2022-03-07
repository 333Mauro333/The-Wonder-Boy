#include "gameplay_1.h"

#include <iostream>

#include "game_manager/game_manager.h"
#include "game_controls/game_controls.h"
#include "scene_manager/scene_manager.h"
#include "curtain_manager/curtain_manager.h"
#include "game_scenes/screens/main_menu/main_menu.h"
#include "collision_manager/collision_manager.h"
#include "enemies/snail/snail.h"
#include "enemies/wasp/wasp.h"

using std::cout;


namespace the_wonder_boy
{
	Gameplay1::Gameplay1(RenderWindow* window) : Scene(window)
	{
		cout << "Se ha creado un nivel de gameplay.\n\n";

		reseted = true;
		end = false;
		changeScene = false;

		if (!font.loadFromFile("res/fonts/retro.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}
		winMessage.setFont(font);
		winMessage.setString("¡Enhorabuena! ¡Has finalizado\n          el nivel!\n  Presione ENTER para volver\n      al menú principal.");
		winMessage.setCharacterSize(30);
		winMessage.setFillColor(sf::Color::Black);
		winMessage.setOrigin(winMessage.getGlobalBounds().width / 2.0f, winMessage.getGlobalBounds().height / 2.0f);

		if (!music.openFromFile("res/tracks/track_gameplay.ogg"))
		{
			cout << "La musica del gameplay no se ha cargado.\n";
		}
		music.play();

		CurtainManager::startToShow(CURTAIN_TYPE::FADE);
		Player::setAmountOfLives(5);
		Player::setAmountOfPoints(0);

		init();
	}
	Gameplay1::~Gameplay1()
	{
		cout << "El nivel de gameplay ha sido eliminado de la memoria.\n";
	}


	// Funciones públicas.
	void Gameplay1::update()
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
		for (int i = 0; i < platformSize; i++)
		{
			if (CollisionManager::isColliding(player, platform[i]))
			{
				player->collisionWith(platform[i]);
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
		if (CollisionManager::isColliding(player, sprHammer))
		{
			player->collisionWith(sprHammer);
			sprHammer.setPosition(0.0f, 0.0f);
		}

		checkIfPlayerWon();

		if (changeScene)
		{
			view.setCenter(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
			CurtainManager::setCurtainPosition(view.getCenter());

			window->setView(view);
			music.stop();
			SceneManager::loadNewScene(new MainMenu(window, SELECTED_OPTION::PLAY));
		}
	}
	void Gameplay1::draw()
	{
		window->draw(background);
		window->draw(sprHammer);
		for (int i = 0; i < signSize; i++)
		{
			sign[i]->draw(window);
		}
		for (int i = 0; i < floorSize; i++)
		{
			floor[i]->draw(window);
		}
		for (int i = 0; i < platformSize; i++)
		{
			platform[i]->draw(window);
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

		if (end)
		{
			window->draw(winMessage);
		}
	}
	void Gameplay1::checkKeyPressedOnce(Keyboard::Key key)
	{
		player->keyPressedOnce(key);

		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::screenReturn)))
		{
			view.setCenter(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
			CurtainManager::setCurtainPosition(view.getCenter());

			window->setView(view);
			music.stop();
			SceneManager::loadNewScene(new MainMenu(window, SELECTED_OPTION::PLAY));
		}
		if (end && Keyboard::isKeyPressed(static_cast<Keyboard::Key>(Keyboard::Enter)))
		{
			view.setCenter(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
			CurtainManager::setCurtainPosition(view.getCenter());

			window->setView(view);
			music.stop();
			SceneManager::loadNewScene(new MainMenu(window, SELECTED_OPTION::PLAY));
		}
	}
	void Gameplay1::checkKeyReleased(Keyboard::Key key)
	{
		player->keyReleased(key);
	}


	// Funciones privadas.
	void Gameplay1::init()
	{
		// Color del fondo.
		background.setSize(static_cast<Vector2f>(window->getSize()));
		background.setFillColor(sf::Color(128, 128, 255)); // Celeste.
		background.setOrigin(background.getGlobalBounds().width / 2.0f, background.getGlobalBounds().height / 2.0f);

		// Pisos.
		float x = 0.0f;
		float y = window->getSize().y / 4.0f * 3.5f;
		for (int i = 0; i < 44; i++)
		{
			if (i == 43)
			{
				floor[i] = new Floor(x, y, FLOOR_TYPE::END);
				x -= floor[i - 1]->getBoxCollision().getGlobalBounds().width;
				x += floor[i]->getBoxCollision().getGlobalBounds().width;
				floor[i]->setPosition(x, y);
				x += floor[i]->getBoxCollision().getGlobalBounds().width * 2;
			}
			else
			{
				floor[i] = new Floor(x, y, FLOOR_TYPE::NORMAL);
			}

			x += floor[i]->getBoxCollision().getGlobalBounds().width; // 300 de ancho.
		}
		x = 14700.0f;
		y = 0.0f;
		for (int i = 44; i < 66; i++)
		{
			if (i == 44)
			{
				floor[i] = new Floor(x, y, FLOOR_TYPE::START);
			}
			else if (i == 65)
			{
				x -= floor[i - 1]->getBoxCollision().getGlobalBounds().width; // 300 de ancho.
				floor[i] = new Floor(x, y, FLOOR_TYPE::END);
				floor[i]->setPosition(floor[i]->getInitialPosition().x + floor[i]->getBoxCollision().getGlobalBounds().width, floor[i]->getInitialPosition().y);
			}
			else
			{
				floor[i] = new Floor(x, y, FLOOR_TYPE::NORMAL);
			}

			x += floor[i]->getBoxCollision().getGlobalBounds().width; // 300 de ancho.
		}
		x = 24800.0f;
		for (int i = 66; i < floorSize; i++)
		{
			if (i == 66)
			{
				floor[i] = new Floor(x, floor[44]->getInitialPosition().y, FLOOR_TYPE::START);
			}
			else
			{
				floor[i] = new Floor(x, floor[44]->getInitialPosition().y, FLOOR_TYPE::NORMAL);
			}

			x += floor[i]->getBoxCollision().getGlobalBounds().width;
		}



		// Plataforma(s).
		x = 13300.0f;
		y = 500.0f;
		platform[0] = new Platform(x, y);
		platform[1] = new Platform(x + 400.0f, y - 200.0f);
		platform[2] = new Platform(x + 800.0f, y - 400.0f);
		x = 20500.0f + 800.0f;
		y = floor[44]->getInitialPosition().y - 100.0f;

		for (int i = 3; i < platformSize; i++)
		{
			platform[i] = new Platform(x, y);

			x += 550.0f;
			if (i % 2 == 0)
			{
				y -= 200.0f;
			}
			else
			{
				y += 200.0f;
			}
		}

		// Señales.
		x = floor[1]->getInitialPosition().x;
		y = floor[1]->getInitialPosition().y;
		sign[0] = new Sign(x, y, SIGN_TYPE::FIRST);
		sign[1] = new Sign(8500.0f, y, SIGN_TYPE::SECOND);
		sign[2] = new Sign(15500.0f, floor[44]->getInitialPosition().y, SIGN_TYPE::THIRD);
		sign[3] = new Sign(20500.0f, floor[44]->getInitialPosition().y, SIGN_TYPE::FOURTH);
		sign[4] = new Sign(25000.0f, floor[44]->getInitialPosition().y, SIGN_TYPE::GOAL);


		// Frutas.
		x = floor[3]->getInitialPosition().x;
		y = floor[4]->getInitialPosition().y - 100.0f;
		// ---- SEÑAL 1 --- //
		fruit[0] = new Fruit(x, y, FRUIT_TYPE::APPLE);
		fruit[1] = new Fruit(x + 900.0f, y - 200.0f, FRUIT_TYPE::APPLE);
		fruit[2] = new Fruit(x + 975.0f, y - 200.0f, FRUIT_TYPE::APPLE);
		fruit[3] = new Fruit(x + 1500.0f, y, FRUIT_TYPE::BANANAS);
		fruit[4] = new Fruit(x + 2000.0f, y - 200.0f, FRUIT_TYPE::CARROT);

		fruit[5] = new Fruit(x + 2400.0f, y - 25.0f, FRUIT_TYPE::APPLE);
		fruit[6] = new Fruit(x + 2500.0f, y - 25.0f, FRUIT_TYPE::BANANAS);
		fruit[7] = new Fruit(x + 2600.0f, y - 25.0f, FRUIT_TYPE::CARROT);
		fruit[8] = new Fruit(x + 2700.0f, y - 25.0f, FRUIT_TYPE::TOMATO);
		fruit[9] = new Fruit(x + 2800.0f, y - 25.0f, FRUIT_TYPE::TOMATO);
		fruit[10] = new Fruit(6600.0f, y -200.0f, FRUIT_TYPE::TOMATO);
		// ---- SEÑAL 1 --- //
		// ---- SEÑAL 2 --- //
		fruit[11] = new Fruit(sign[1]->getRenderer().getPosition().x + 1000.0f, y - 200.0f, FRUIT_TYPE::TOMATO);
		fruit[12] = new Fruit(10000.0f + 1500.0f, y - 200.0f, FRUIT_TYPE::BANANAS);
		fruit[13] = new Fruit(10000.0f + 2200.0f, y - 50.0f, FRUIT_TYPE::CARROT);
		fruit[14] = new Fruit(10000.0f + 2300.0f, y - 50.0f, FRUIT_TYPE::CARROT);
		// ---- SEÑAL 2 --- //
		// ---- SEÑAL 3 --- //
		x = sign[2]->getRenderer().getPosition().x;
		y = sign[2]->getRenderer().getPosition().y - 100.0f;
		fruit[15] = new Fruit(x + 300.0f, y - 50.0f, FRUIT_TYPE::APPLE);
		fruit[16] = new Fruit(x + 300.0f, y - 50.0f, FRUIT_TYPE::BANANAS);
		fruit[17] = new Fruit(x + 300.0f, y - 50.0f, FRUIT_TYPE::CARROT);
		fruit[18] = new Fruit(x + 300.0f, y - 50.0f, FRUIT_TYPE::TOMATO);
		x = sign[2]->getRenderer().getPosition().x + 1000.0f;
		for (int i = 19; i < fruitSize; i++)
		{
			if (i % 4 == 0)
			{
				fruit[i] = new Fruit(x, y - 150, FRUIT_TYPE::BANANAS);
			}
			else if (i % 4 == 1)
			{
				fruit[i] = new Fruit(x, y - 150, FRUIT_TYPE::CARROT);
			}
			else if (i % 4 == 2)
			{
				fruit[i] = new Fruit(x, y - 150, FRUIT_TYPE::TOMATO);
			}
			else
			{
				fruit[i] = new Fruit(x, y - 150, FRUIT_TYPE::APPLE);
			}

			x += 200.0f;
		}
		// --- SEÑAL 4 --- //


		// Piedras.
		x = floor[10]->getInitialPosition().x;
		y = floor[10]->getInitialPosition().y;
		// ---- SEÑAL 1 --- //
		stone[0] = new Stone(x, y);
		stone[1] = new Stone(x + 1200.0f, y);
		stone[2] = new Stone(x + 1300.0f, y);
		stone[3] = new Stone(6600.0f, y);
		stone[4] = new Stone(6700.0f, y);
		stone[5] = new Stone(6800.0f, y);
		// ---- SEÑAL 1 --- //
		// ---- SEÑAL 2 --- //

		// ---- SEÑAL 2 --- //


		// Fogata(s).
		x = 10000.0f;
		y = floor[12]->getInitialPosition().y;
		// ---- SEÑAL 2 --- //
		bonfire[0] = new Bonfire(x, y);
		// ---- SEÑAL 2 --- //
		x = sign[2]->getRenderer().getPosition().x;
		y = sign[2]->getRenderer().getPosition().y;
		bonfire[1] = new Bonfire(x + 1500.0f, y);
		bonfire[2] = new Bonfire(x + 2000.0f, y);
		bonfire[3] = new Bonfire(x + 2500.0f, y);
		bonfire[4] = new Bonfire(x + 3000.0f, y);

		// Enemigos.
		x = 6000.0f;
		y = floor[15]->getInitialPosition().y;
		// ---- SEÑAL 1 --- //
		enemy[0] = new Snail(x, y);
		enemy[1] = new Snail(x + 200.0f, y);

		enemy[2] = new Snail(x + 1200.0f + 200.0f, y);
		enemy[3] = new Snail(x + 1350.0f + 200.0f, y);
		enemy[4] = new Snail(x + 1700.0f + 200.0f, y);
		// ---- SEÑAL 1 --- //
		// ---- SEÑAL 2 --- //
		x = 10000.0f;
		enemy[5] = new Wasp(x + 500.0f, y - 125.0f, WASP_VERTICAL_SPEED::SLOW);
		enemy[6] = new Wasp(x + 600.0f, y - 50.0f, WASP_VERTICAL_SPEED::NORMAL);
		enemy[7] = new Snail(x + 900.0f, y);
		enemy[8] = new Snail(x + 1050.0f, y);
		// ---- SEÑAL 2 --- //
		// ---- SEÑAL 3 --- //
		x = sign[2]->getRenderer().getPosition().x + 2000.0f;
		y = sign[2]->getRenderer().getPosition().y;
		for (int i = 9; i < enemySize; i++)
		{
			cout << "Se ejecuta.\n";
			if (i % 3 == 0)
			{
				enemy[i] = new Snail(x, y);
			}
			else
			{
				if (i < 25)
				{
					enemy[i] = new Wasp(x, y - 150.0f, WASP_VERTICAL_SPEED::NORMAL);
				}
				else
				{
					enemy[i] = new Wasp(x, y - 150.0f, WASP_VERTICAL_SPEED::FAST);
				}
			}

			x += 100.0f;
		}

		// Jugador.
		player = new Player(sign[0]->getRenderer().getPosition().x, sign[0]->getRenderer().getPosition().y);
		player->setNecessaryDistanceToWin(sign[4]->getRenderer().getPosition().x + sign[4]->getRenderer().getGlobalBounds().width);

		view.setSize(Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
		view.setCenter(player->getPosition().x, player->getPosition().y - window->getSize().y / 4.0f);
		CurtainManager::setCurtainPosition(view.getCenter());

		window->setView(view);

		hud = new HUD(window, player);

		if (!texHammer.loadFromFile("res/sprites/items/other/hammer.png"))
		{
			cout << "La textura hammer.png no se ha cargado.\n";
		}
		sprHammer.setTexture(texHammer);
		sprHammer.setOrigin(sprHammer.getGlobalBounds().width / 2.0f, sprHammer.getGlobalBounds().height / 2.0f);
		sprHammer.setPosition(5300.0f, floor[12]->getInitialPosition().y - 100.0f);
	}
	void Gameplay1::destroy()
	{

	}

	void Gameplay1::moveCameraInY(float start, float end, float pixelsToMove)
	{
		if (player->getPosition().x >= start && player->getPosition().x <= end)
		{
			float distanceTrayectory = end - start; // Distancia total de principio a fin.

			// Movimiento total / distancia entre la que se va a mover * velocidad del jugador en cada frame.
			view.setCenter(view.getCenter().x, view.getCenter().y + pixelsToMove / distanceTrayectory * player->getSpeed() * GameManager::getDeltaTime());
		}
	}
	void Gameplay1::updateCamera()
	{
		const float distanceToCenter = static_cast<float>(window->getSize().x) / 10.0f;
		const float playerRightEdgePosition = player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x + player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f;
		const float playerLeftEdgePosition = player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f;


		// Si el jugador avanza lo suficiente hacia la derecha...
		if (playerRightEdgePosition + distanceToCenter > view.getCenter().x)
		{
			moveCameraInY(13200.0f, 14400.0f, -650.0f);

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

		// Si el jugador cruza el borde inferior de la ventana...
		if (player->getPosition().y > view.getCenter().y + view.getSize().y / 1.5f)
		{
			// Pierde.
			player->lose(LOSING_TYPE::NORMAL);
		}

		if (!player->isAlive() && player->getPosition().y > view.getCenter().y + view.getSize().y)
		{
			resetLevel();
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
			float distanceToBeActivated = view.getSize().x / 2.0f;

			if (!fruit[i]->isActive() && !fruit[i]->wasTaken() && player->getPosition().x + distanceToBeActivated > fruit[i]->getPosition().x)
			{
				if (!reseted)
				{
					fruit[i]->activate();
					cout << "Se ha activado la fruta " << i + 1 << ".\n";
				}
				else
				{
					if (player->getPosition().x + distanceToBeActivated / 1.5f < fruit[i]->getPosition().x)
					{
						fruit[i]->activate();
						cout << "Se ha activado la fruta " << i + 1 << ".\n";
					}
				}
			}
		}

		background.setPosition(view.getCenter());
		CurtainManager::setCurtainPosition(view.getCenter());

		window->setView(view); // Se le pasa a la ventana la view actualizada.
	}

	Vector2f Gameplay1::getPlayerCheckpointPosition()
	{
		int checkPointNumber = 3;

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

	void Gameplay1::resetLevel()
	{
		if (Player::getLives() > 0)
		{
			reseted = true;

			player->subtractLife();
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

			#pragma region POSICIONAMIENTO DE LA CÁMARA

			const float distanceToCenter = static_cast<float>(window->getSize().x) / 10.0f;
			const float playerRightEdgePosition = player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x + player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f;

			view.setCenter(playerRightEdgePosition + distanceToCenter, player->getPosition().y - window->getSize().y / 4.0f);

			#pragma endregion

			window->setView(view);
		}
		else
		{
			changeScene = true;
		}
	}

	void Gameplay1::checkIfPlayerWon()
	{
		if (!end && player->won())
		{
			end = true;

			winMessage.setPosition(view.getCenter().x, view.getCenter().y - view.getSize().y / 8.0f);
		}
	}
}
