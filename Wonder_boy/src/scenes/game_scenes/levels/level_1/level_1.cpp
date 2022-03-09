#include "level_1.h"

#include <iostream>

#include "game_manager/game_manager.h"
#include "controls_manager/controls_manager.h"
#include "scene_manager/scene_manager.h"
#include "curtain_manager/curtain_manager.h"
#include "scenes/game_scenes/screens/main_menu/main_menu.h"
#include "collision_manager/collision_manager.h"
#include "gameplay_elements/enemies/snail/snail.h"
#include "gameplay_elements/enemies/wasp/wasp.h"

using std::cout;


namespace the_wonder_boy
{
	Level1::Level1(RenderWindow* window) : Scene(window)
	{
		cout << "Se ha creado un nivel de gameplay.\n\n";

		_reseted = true;
		_end = false;
		_changeScene = false;

		if (!_font.loadFromFile("res/fonts/retro.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}
		_winMessage.setFont(_font);
		_winMessage.setString("¡Enhorabuena! ¡Has finalizado\n          el nivel!\n  Presione ENTER para volver\n      al menú principal.");
		_winMessage.setCharacterSize(30);
		_winMessage.setFillColor(sf::Color::Black);
		_winMessage.setOrigin(_winMessage.getGlobalBounds().width / 2.0f, _winMessage.getGlobalBounds().height / 2.0f);

		if (!_music.openFromFile("res/tracks/track_gameplay.ogg"))
		{
			cout << "La musica del gameplay no se ha cargado.\n";
		}
		_music.play();
		_music.setLoop(true);

		CurtainManager::startToShow(CURTAIN_TYPE::FADE);
		Player::setAmountOfLives(5);
		Player::setAmountOfPoints(0);

		init();
	}
	Level1::~Level1()
	{
		destroy();

		cout << "El nivel de gameplay ha sido eliminado de la memoria.\n";
	}


	// Funciones públicas.
	void Level1::update()
	{
		_player->update(GameManager::getDeltaTime());

		updateCamera();

		_hud->update();

		for (int i = 0; i < _floorSize; i++)
		{
			for (int j = 0; j < Player::getStoneHammersSize(); j++)
			{
				if (CollisionManager::isColliding(_player->getPlayerStoneHammer(j), _floor[i]))
				{
					_player->getPlayerStoneHammer(j)->hit();
				}
			}

			if (CollisionManager::isColliding(_player, _floor[i]))
			{
				_player->collisionWith(_floor[i]);
			}
		}
		for (int i = 0; i < _platformSize; i++)
		{
			if (CollisionManager::isColliding(_player, _platform[i]))
			{
				_player->collisionWith(_platform[i]);
			}
		}
		for (int i = 0; i < _fruitSize; i++)
		{
			_fruit[i]->update(GameManager::getDeltaTime());

			if (CollisionManager::isColliding(_player, _fruit[i]))
			{
				_fruit[i]->take();
				_player->addHealth(_fruit[i]->getHealthValue());
				_player->addPoints(_fruit[i]->getPointsValue());
				cout << "La fruta " << i + 1 << " fue agarrada.\n";
			}
		}
		for (int i = 0; i < _stoneSize; i++)
		{
			if (CollisionManager::isColliding(_player, _stone[i]) && !_player->getHit())
			{
				_player->tripOn(_stone[i]);
				cout << "Esta tocando la piedra " << i + 1 << ".\n";
			}
		}
		for (int i = 0; i < _bonfireSize; i++)
		{
			_bonfire[i]->update(GameManager::getDeltaTime());

			if (CollisionManager::isColliding(_player, _bonfire[i]))
			{
				_player->lose(LOSING_TYPE::BURNED);
				cout << "Se quemo con la fogata  " << i + 1 << ".\n";
			}
		}
		for (int i = 0; i < _enemySize; i++)
		{
			_enemy[i]->update(GameManager::getDeltaTime());

			if (CollisionManager::isColliding(_player, _enemy[i]))
			{
				_player->lose(LOSING_TYPE::NORMAL);
			}

			for (int j = 0; j < Player::getStoneHammersSize(); j++)
			{
				if (CollisionManager::isColliding(_player->getPlayerStoneHammer(j), _enemy[i]))
				{
					_enemy[i]->defeat();
					_player->getPlayerStoneHammer(j)->hit();
					_player->addPoints(_enemy[i]->getPoints());
					cout << "El enemigo pierde.\n";
				}
			}
		}
		if (CollisionManager::isColliding(_player, _sprHammer))
		{
			_player->collisionWith(_sprHammer);
			_sprHammer.setPosition(0.0f, 0.0f);
		}

		checkIfPlayerWon();

		if (_changeScene)
		{
			_view.setCenter(_window->getSize().x / 2.0f, _window->getSize().y / 2.0f);
			CurtainManager::setCurtainPosition(_view.getCenter());

			_window->setView(_view);
			_music.stop();
			SceneManager::loadNewScene(new MainMenu(_window, SELECTED_OPTION::PLAY));
		}
	}
	void Level1::draw()
	{
		_window->draw(_background);
		_window->draw(_sprHammer);
		for (int i = 0; i < _signSize; i++)
		{
			_sign[i]->draw(_window);
		}
		for (int i = 0; i < _floorSize; i++)
		{
			_floor[i]->draw(_window);
		}
		for (int i = 0; i < _platformSize; i++)
		{
			_platform[i]->draw(_window);
		}
		_player->draw(_window);
		for (int i = 0; i < _fruitSize; i++)
		{
			_fruit[i]->draw(_window);
		}
		for (int i = 0; i < _enemySize; i++)
		{
			_enemy[i]->draw(_window);
		}
		for (int i = 0; i < _stoneSize; i++)
		{
			_stone[i]->draw(_window);
		}
		for (int i = 0; i < _bonfireSize; i++)
		{
			_bonfire[i]->draw(_window);
		}
		_hud->draw(_window);

		if (_end)
		{
			_window->draw(_winMessage);
		}
	}
	void Level1::checkKeyPressedOnce(Keyboard::Key key)
	{
		_player->keyPressedOnce(key);

		if (Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::SCREEN_RETURN)))
		{
			_view.setCenter(_window->getSize().x / 2.0f, _window->getSize().y / 2.0f);
			CurtainManager::setCurtainPosition(_view.getCenter());

			_window->setView(_view);
			_music.stop();
			SceneManager::loadNewScene(new MainMenu(_window, SELECTED_OPTION::PLAY));
		}
		if (_end && Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::SCREEN_ENTER)))
		{
			_view.setCenter(_window->getSize().x / 2.0f, _window->getSize().y / 2.0f);
			CurtainManager::setCurtainPosition(_view.getCenter());

			_window->setView(_view);
			_music.stop();
			SceneManager::loadNewScene(new MainMenu(_window, SELECTED_OPTION::PLAY));
		}
	}
	void Level1::checkKeyReleased(Keyboard::Key key)
	{
		_player->keyReleased(key);
	}


	// Funciones privadas.
	void Level1::init()
	{
		// Color del fondo.
		_background.setSize(static_cast<Vector2f>(_window->getSize()));
		_background.setFillColor(sf::Color(128, 128, 255)); // Celeste.
		_background.setOrigin(_background.getGlobalBounds().width / 2.0f, _background.getGlobalBounds().height / 2.0f);


		// Pisos.
		float x = 0.0f;
		float y = _window->getSize().y / 4.0f * 3.5f;
		for (int i = 0; i < 44; i++)
		{
			if (i == 43)
			{
				_floor[i] = new Floor(x, y, FLOOR_TYPE::END);
				x -= _floor[i - 1]->getBoxCollision().getGlobalBounds().width;
				x += _floor[i]->getBoxCollision().getGlobalBounds().width;
				_floor[i]->setPosition(x, y);
				x += _floor[i]->getBoxCollision().getGlobalBounds().width * 2;
			}
			else
			{
				_floor[i] = new Floor(x, y, FLOOR_TYPE::NORMAL);
			}

			x += _floor[i]->getBoxCollision().getGlobalBounds().width; // 300 de ancho.
		}
		x = 14700.0f;
		y = 0.0f;
		for (int i = 44; i < 66; i++)
		{
			if (i == 44)
			{
				_floor[i] = new Floor(x, y, FLOOR_TYPE::START);
			}
			else if (i == 65)
			{
				x -= _floor[i - 1]->getBoxCollision().getGlobalBounds().width; // 300 de ancho.
				_floor[i] = new Floor(x, y, FLOOR_TYPE::END);
				_floor[i]->setPosition(_floor[i]->getInitialPosition().x + _floor[i]->getBoxCollision().getGlobalBounds().width, _floor[i]->getInitialPosition().y);
			}
			else
			{
				_floor[i] = new Floor(x, y, FLOOR_TYPE::NORMAL);
			}

			x += _floor[i]->getBoxCollision().getGlobalBounds().width; // 300 de ancho.
		}
		x = 24800.0f;
		for (int i = 66; i < _floorSize; i++)
		{
			if (i == 66)
			{
				_floor[i] = new Floor(x, _floor[44]->getInitialPosition().y, FLOOR_TYPE::START);
			}
			else
			{
				_floor[i] = new Floor(x, _floor[44]->getInitialPosition().y, FLOOR_TYPE::NORMAL);
			}

			x += _floor[i]->getBoxCollision().getGlobalBounds().width;
		}


		// Plataforma(s).
		x = 13300.0f;
		y = 500.0f;
		_platform[0] = new Platform(x, y);
		_platform[1] = new Platform(x + 400.0f, y - 200.0f);
		_platform[2] = new Platform(x + 800.0f, y - 400.0f);
		x = 20500.0f + 800.0f;
		y = _floor[44]->getInitialPosition().y - 100.0f;

		for (int i = 3; i < _platformSize; i++)
		{
			_platform[i] = new Platform(x, y);

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
		x = _floor[1]->getInitialPosition().x;
		y = _floor[1]->getInitialPosition().y;
		_sign[0] = new Sign(x, y, SIGN_TYPE::FIRST);
		_sign[1] = new Sign(8500.0f, y, SIGN_TYPE::SECOND);
		_sign[2] = new Sign(15500.0f, _floor[44]->getInitialPosition().y, SIGN_TYPE::THIRD);
		_sign[3] = new Sign(20500.0f, _floor[44]->getInitialPosition().y, SIGN_TYPE::FOURTH);
		_sign[4] = new Sign(25000.0f, _floor[44]->getInitialPosition().y, SIGN_TYPE::GOAL);


		// Frutas.
		x = _floor[3]->getInitialPosition().x;
		y = _floor[4]->getInitialPosition().y - 100.0f;
		// ---- SEÑAL 1 --- //
		_fruit[0] = new Fruit(x, y, FRUIT_TYPE::APPLE);
		_fruit[1] = new Fruit(x + 900.0f, y - 200.0f, FRUIT_TYPE::APPLE);
		_fruit[2] = new Fruit(x + 975.0f, y - 200.0f, FRUIT_TYPE::APPLE);
		_fruit[3] = new Fruit(x + 1500.0f, y, FRUIT_TYPE::BANANAS);
		_fruit[4] = new Fruit(x + 2000.0f, y - 200.0f, FRUIT_TYPE::CARROT);

		_fruit[5] = new Fruit(x + 2400.0f, y - 25.0f, FRUIT_TYPE::APPLE);
		_fruit[6] = new Fruit(x + 2500.0f, y - 25.0f, FRUIT_TYPE::BANANAS);
		_fruit[7] = new Fruit(x + 2600.0f, y - 25.0f, FRUIT_TYPE::CARROT);
		_fruit[8] = new Fruit(x + 2700.0f, y - 25.0f, FRUIT_TYPE::TOMATO);
		_fruit[9] = new Fruit(x + 2800.0f, y - 25.0f, FRUIT_TYPE::TOMATO);
		_fruit[10] = new Fruit(6600.0f, y -200.0f, FRUIT_TYPE::TOMATO);
		// ---- SEÑAL 1 --- //
		// ---- SEÑAL 2 --- //
		_fruit[11] = new Fruit(_sign[1]->getRenderer().getPosition().x + 1000.0f, y - 200.0f, FRUIT_TYPE::TOMATO);
		_fruit[12] = new Fruit(10000.0f + 1500.0f, y - 200.0f, FRUIT_TYPE::BANANAS);
		_fruit[13] = new Fruit(10000.0f + 2200.0f, y - 50.0f, FRUIT_TYPE::CARROT);
		_fruit[14] = new Fruit(10000.0f + 2300.0f, y - 50.0f, FRUIT_TYPE::CARROT);
		// ---- SEÑAL 2 --- //
		// ---- SEÑAL 3 --- //
		x = _sign[2]->getRenderer().getPosition().x;
		y = _sign[2]->getRenderer().getPosition().y - 100.0f;
		_fruit[15] = new Fruit(x + 300.0f, y - 50.0f, FRUIT_TYPE::APPLE);
		_fruit[16] = new Fruit(x + 300.0f, y - 50.0f, FRUIT_TYPE::BANANAS);
		_fruit[17] = new Fruit(x + 300.0f, y - 50.0f, FRUIT_TYPE::CARROT);
		_fruit[18] = new Fruit(x + 300.0f, y - 50.0f, FRUIT_TYPE::TOMATO);
		x = _sign[2]->getRenderer().getPosition().x + 1000.0f;
		for (int i = 19; i < _fruitSize; i++)
		{
			if (i % 4 == 0)
			{
				_fruit[i] = new Fruit(x, y - 150, FRUIT_TYPE::BANANAS);
			}
			else if (i % 4 == 1)
			{
				_fruit[i] = new Fruit(x, y - 150, FRUIT_TYPE::CARROT);
			}
			else if (i % 4 == 2)
			{
				_fruit[i] = new Fruit(x, y - 150, FRUIT_TYPE::TOMATO);
			}
			else
			{
				_fruit[i] = new Fruit(x, y - 150, FRUIT_TYPE::APPLE);
			}

			x += 200.0f;
		}
		// --- SEÑAL 4 --- //


		// Piedras.
		x = _floor[10]->getInitialPosition().x;
		y = _floor[10]->getInitialPosition().y;
		// ---- SEÑAL 1 --- //
		_stone[0] = new Stone(x, y);
		_stone[1] = new Stone(x + 1200.0f, y);
		_stone[2] = new Stone(x + 1300.0f, y);
		_stone[3] = new Stone(6600.0f, y);
		_stone[4] = new Stone(6700.0f, y);
		_stone[5] = new Stone(6800.0f, y);
		// ---- SEÑAL 1 --- //
		// ---- SEÑAL 2 --- //

		// ---- SEÑAL 2 --- //


		// Fogata(s).
		x = 10000.0f;
		y = _floor[12]->getInitialPosition().y;
		// ---- SEÑAL 2 --- //
		_bonfire[0] = new Bonfire(x, y);
		// ---- SEÑAL 2 --- //
		x = _sign[2]->getRenderer().getPosition().x;
		y = _sign[2]->getRenderer().getPosition().y;
		_bonfire[1] = new Bonfire(x + 1500.0f, y);
		_bonfire[2] = new Bonfire(x + 2000.0f, y);
		_bonfire[3] = new Bonfire(x + 2500.0f, y);
		_bonfire[4] = new Bonfire(x + 3000.0f, y);

		// Enemigos.
		x = 6000.0f;
		y = _floor[15]->getInitialPosition().y;
		// ---- SEÑAL 1 --- //
		_enemy[0] = new Snail(x, y);
		_enemy[1] = new Snail(x + 200.0f, y);

		_enemy[2] = new Snail(x + 1200.0f + 200.0f, y);
		_enemy[3] = new Snail(x + 1350.0f + 200.0f, y);
		_enemy[4] = new Snail(x + 1700.0f + 200.0f, y);
		// ---- SEÑAL 1 --- //
		// ---- SEÑAL 2 --- //
		x = 10000.0f;
		_enemy[5] = new Wasp(x + 500.0f, y - 125.0f, WASP_VERTICAL_SPEED::SLOW);
		_enemy[6] = new Wasp(x + 600.0f, y - 50.0f, WASP_VERTICAL_SPEED::NORMAL);
		_enemy[7] = new Snail(x + 900.0f, y);
		_enemy[8] = new Snail(x + 1050.0f, y);
		// ---- SEÑAL 2 --- //
		// ---- SEÑAL 3 --- //
		x = _sign[2]->getRenderer().getPosition().x + 2000.0f;
		y = _sign[2]->getRenderer().getPosition().y;
		for (int i = 9; i < _enemySize; i++)
		{
			cout << "Se ejecuta.\n";
			if (i % 3 == 0)
			{
				_enemy[i] = new Snail(x, y);
			}
			else
			{
				if (i < 25)
				{
					_enemy[i] = new Wasp(x, y - 150.0f, WASP_VERTICAL_SPEED::NORMAL);
				}
				else
				{
					_enemy[i] = new Wasp(x, y - 150.0f, WASP_VERTICAL_SPEED::FAST);
				}
			}

			x += 100.0f;
		}

		// Jugador.
		_player = new Player(_sign[0]->getRenderer().getPosition().x, _sign[0]->getRenderer().getPosition().y);
		_player->setNecessaryDistanceToWin(_sign[4]->getRenderer().getPosition().x + _sign[4]->getRenderer().getGlobalBounds().width);

		_view.setSize(Vector2f(static_cast<float>(_window->getSize().x), static_cast<float>(_window->getSize().y)));
		_view.setCenter(_player->getPosition().x, _player->getPosition().y - _window->getSize().y / 4.0f);
		CurtainManager::setCurtainPosition(_view.getCenter());

		_window->setView(_view);

		_hud = new HUD(_window, _player);

		if (!_texHammer.loadFromFile("res/sprites/items/other/hammer.png"))
		{
			cout << "La textura hammer.png no se ha cargado.\n";
		}
		_sprHammer.setTexture(_texHammer);
		_sprHammer.setOrigin(_sprHammer.getGlobalBounds().width / 2.0f, _sprHammer.getGlobalBounds().height / 2.0f);
		_sprHammer.setPosition(5300.0f, _floor[12]->getInitialPosition().y - 100.0f);
	}
	void Level1::destroy()
	{
		delete _player;
		delete _hud;

		for (int i = 0; i < _floorSize; i++)
		{
			delete _floor[i];
		}
		for (int i = 0; i < _platformSize; i++)
		{
			delete _platform[i];
		}
		for (int i = 0; i < _signSize; i++)
		{
			delete _sign[i];
		}
		for (int i = 0; i < _fruitSize; i++)
		{
			delete _fruit[i];
		}
		for (int i = 0; i < _stoneSize; i++)
		{
			delete _stone[i];
		}
		for (int i = 0; i < _bonfireSize; i++)
		{
			delete _bonfire[i];
		}
		for (int i = 0; i < _enemySize; i++)
		{
			delete _enemy[i];
		}
	}

	void Level1::moveCameraInY(float start, float end, float pixelsToMove)
	{
		if (_player->getPosition().x >= start && _player->getPosition().x <= end)
		{
			const float distanceTrayectory = end - start; // Distancia total de principio a fin.

			// Movimiento total / distancia entre la que se va a mover * velocidad del jugador en cada frame.
			_view.setCenter(_view.getCenter().x, _view.getCenter().y + pixelsToMove / distanceTrayectory * _player->getSpeed() * GameManager::getDeltaTime());
		}
	}
	void Level1::updateCamera()
	{
		const float distanceToCenter = static_cast<float>(_window->getSize().x) / 10.0f;
		const float playerRightEdgePosition = _player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x + _player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f;
		const float playerLeftEdgePosition = _player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x - _player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f;


		// Si el jugador avanza lo suficiente hacia la derecha...
		if (playerRightEdgePosition + distanceToCenter > _view.getCenter().x)
		{
			moveCameraInY(13200.0f, 14400.0f, -650.0f);

			// ...lo sigue la cámara.
			_view.setCenter(playerRightEdgePosition + distanceToCenter, _view.getCenter().y);
		}

		// Si el jugador choca contra el límite izquierdo de la pantalla...
		if (playerLeftEdgePosition < _view.getCenter().x - _view.getSize().x / 2.0f)
		{
			// ...no puede retroceder más.
			_player->setPosition(Vector2f(_view.getCenter().x - _view.getSize().x / 2.0f + _player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f, _player->getPosition().y));
			_player->stopWalkSpeed();
		}

		// Si el jugador cruza el borde inferior de la ventana...
		if (_player->getPosition().y > _view.getCenter().y + _view.getSize().y / 1.5f)
		{
			// Pierde.
			_player->lose(LOSING_TYPE::NORMAL);
		}

		if (!_player->isAlive() && _player->getPosition().y > _view.getCenter().y + _view.getSize().y)
		{
			resetLevel();
		}
		for (int i = 0; i < Player::getStoneHammersSize(); i++)
		{
			if (_player->getPlayerStoneHammer(i)->getIsThrown() && _player->getPlayerStoneHammer(i)->getPosition().y > _view.getCenter().y + _view.getSize().y / 1.5f)
			{
				_player->getPlayerStoneHammer(i)->hit();
			}
		}
		for (int i = 0; i < _enemySize; i++)
		{
			const float distanceToBeActivated = _view.getSize().x;

			if (!_enemy[i]->isActive() && !_enemy[i]->isDefeated() && _player->getPosition().x + distanceToBeActivated > _enemy[i]->getPosition().x)
			{
				if (!_reseted)
				{
					_enemy[i]->setActive(true);
					cout << "Se ha activado el enemigo " << i + 1 << ".\n";
				}
				else
				{
					if (_player->getPosition().x + distanceToBeActivated / 1.5f < _enemy[i]->getPosition().x)
					{
						_enemy[i]->setActive(true);
						cout << "Se ha activado el enemigo " << i + 1 << ".\n";
					}
				}
			}
			else if (_enemy[i]->isDefeated() && _enemy[i]->isActive() && _enemy[i]->getPosition().y > _view.getCenter().y + _view.getSize().y / 1.5f)
			{
				_enemy[i]->setActive(false);
				cout << "El enemigo " << i + 1 << " fue desactivado.\n";
			}
		}
		for (int i = 0; i < _fruitSize; i++)
		{
			const float distanceToBeActivated = _view.getSize().x / 2.0f;

			if (!_fruit[i]->isActive() && !_fruit[i]->wasTaken() && _player->getPosition().x + distanceToBeActivated > _fruit[i]->getPosition().x)
			{
				if (!_reseted)
				{
					_fruit[i]->activate();
					cout << "Se ha activado la fruta " << i + 1 << ".\n";
				}
				else
				{
					if (_player->getPosition().x + distanceToBeActivated / 1.5f < _fruit[i]->getPosition().x)
					{
						_fruit[i]->activate();
						cout << "Se ha activado la fruta " << i + 1 << ".\n";
					}
				}
			}
		}

		_background.setPosition(_view.getCenter());
		CurtainManager::setCurtainPosition(_view.getCenter());

		_window->setView(_view); // Se le pasa a la ventana la view actualizada.
	}

	Vector2f Level1::getPlayerCheckpointPosition()
	{
		int checkPointNumber = 3;

		for (int i = 0; i < _signSize; i++)
		{
			if (_player->getPosition().x < _sign[i]->getRenderer().getPosition().x - _sign[i]->getRenderer().getGlobalBounds().width)
			{
				checkPointNumber = (i - 1 <= 0) ? 0 : i - 1;
				break;
			}
		}

		return _sign[checkPointNumber]->getRenderer().getPosition();
	}
	void Level1::resetLevel()
	{
		if (Player::getLives() > 0)
		{
			_reseted = true;

			_player->subtractLife();
			_player->reset();
			_player->setPosition(getPlayerCheckpointPosition());

			for (int i = 0; i < _enemySize; i++)
			{
				_enemy[i]->reset();
			}
			for (int i = 0; i < _fruitSize; i++)
			{
				_fruit[i]->reset();
			}

			#pragma region POSICIONAMIENTO DE LA CÁMARA

			const float distanceToCenter = static_cast<float>(_window->getSize().x) / 10.0f;
			const float playerRightEdgePosition = _player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x + _player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getSize().x / 2.0f;

			_view.setCenter(playerRightEdgePosition + distanceToCenter, _player->getPosition().y - _window->getSize().y / 4.0f);

			#pragma endregion

			_window->setView(_view);
		}
		else
		{
			_changeScene = true;
		}
	}
	void Level1::checkIfPlayerWon()
	{
		if (!_end && _player->won())
		{
			_end = true;

			_winMessage.setPosition(_view.getCenter().x, _view.getCenter().y - _view.getSize().y / 8.0f);
		}
	}
}
