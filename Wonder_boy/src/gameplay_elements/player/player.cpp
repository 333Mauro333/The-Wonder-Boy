#include "player.h"

#include <iostream>

#include "controls_manager/controls_manager.h"


using std::cout;


namespace the_wonder_boy
{
	unsigned int Player::_lives = 3;
	unsigned int Player::_points = 0;

	const unsigned int Player::_maxLives = 99;
	const unsigned int Player::_maxHealth = 100;
	const unsigned int Player::_maxPoints = 99999999;

	Player::Player(float x, float y) : Entity(x, y)
	{
		setNewAnimation(ANIMATION_STATE::IDLE_RIGHT); // Defino con qué sprite comienza.

		initAnimations(x, y);

		_renderer.setPosition(x, y);

		_health = 30.0f;
		_canAttack = false;
		_threw = false;
		_hit = false;
		_bouncedWhenDied = false;
		_wins = false;
		_necessaryDistanceToWin = 0.0f;

		_gravity.actualSpeed = 0.0f;
		_gravity.acceleration = 3750.0f;
		_gravity.speedLimit = 1000.0f;
		_gravity.onTheFloor = false;

		_walkingSpeed.actualSpeed = 0.0f;
		_walkingSpeed.acceleration = 2500.0f;
		_walkingSpeed.speedLimit = 500.0f;

		_boxEntire.setFillColor(sf::Color(255, 0, 0, 128));
		_boxEntire.setSize(Vector2f(67, 126));
		_boxEntire.setOrigin(Vector2f(33, 126));

		_boxFeet.setFillColor(sf::Color(255, 0, 0, 128));
		_boxFeet.setSize(Vector2f(67, 20));
		_boxFeet.setOrigin(Vector2f(33, 20));

		for (int i = 0; i < _stoneHammersSize; i++)
		{
			_stoneHammers[i] = new StoneHammer();
		}

		_savedHammerPosition = -1;

		cout << "Se ha creado un jugador.\n\n";
	}
	Player::~Player()
	{
		for (int i = 0; i < _stoneHammersSize; i++)
		{
			delete _stoneHammers[i];
		}

		delete _animIdleLeft;
		delete _animIdleRight;
		delete _animWalkingLeft;
		delete _animWalkingRight;
		delete _animJumpingLeft;
		delete _animJumpingRight;
		delete _animAttackingLeft;
		delete _animAttackingRight;
		delete _animTrippingLeft;
		delete _animTrippingRight;
		delete _animLosingNormal;

		cout << "El jugador ha sido eliminado de la memoria.\n";
	}


	// Funciones públicas.
	void Player::update(float deltaTime)
	{
		checkDistanceToWin();
		drainHealth(deltaTime);
		keyPressed(deltaTime); // Función que verifica si determinadas teclas están siendo presionadas.
		gravityForce(deltaTime); // Aplica la fuerza gravitatoria.
		walkingAccelerationForce(deltaTime); // Aplica la velocidad al caminar.
		updateAnimations(deltaTime); // Actualiza las animaciones.
		accommodateAnimations(); // Acomoda las animaciones a la posición del sprite central.
		updateStoneHammers(deltaTime);
	}
	void Player::draw(RenderWindow* window)
	{
		drawAnimations(window);
		drawStoneHammers(window);

		// Dibujado de las cajas de colisiones.
		#if _DEBUG

		window->draw(_boxEntire);
		window->draw(_boxFeet);

		#endif // _DEBUG
	}
	void Player::keyPressedOnce(Keyboard::Key key)
	{
		if (!_hit && isAlive() && !_wins)
		{
			if (key == ControlsManager::getKey(WANTED_KEY::GAMEPLAY_JUMP))
			{
				if (_gravity.onTheFloor) // Si está en el piso...
				{
					// Orden de verificaciones:
					// 1. Si la tecla de ataque está siendo presionada. Si es así, salta alto.
					// 2. Evalúa las siguientes 2 condiciones para que pueda:
						// a. Que no esté presionando ambos lados a la vez.
						// b. Que esté presionando alguno.
					bool high = Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_ATTACK)) ||
						!bothSidesPressed() &&
						(Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_LEFT)) ||
							Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_RIGHT)));

					jump(high);
				}
			}
			if (key == ControlsManager::getKey(WANTED_KEY::GAMEPLAY_ATTACK))
			{
				const float modifier = 1.5f;

				if (_canAttack)
				{
					switch (_animationState)
					{
					case ANIMATION_STATE::IDLE_RIGHT:
					case ANIMATION_STATE::WALKING_RIGHT:
					case ANIMATION_STATE::JUMPING_RIGHT:
						if (isThereASavedHammer())
						{
							_savedHammerPosition = saveAFreePosition();
							setNewAnimation(ANIMATION_STATE::ATTACKING_RIGHT);
						}
						break;

					case ANIMATION_STATE::IDLE_LEFT:
					case ANIMATION_STATE::WALKING_LEFT:
					case ANIMATION_STATE::JUMPING_LEFT:
						if (isThereASavedHammer())
						{
							_savedHammerPosition = saveAFreePosition();
							setNewAnimation(ANIMATION_STATE::ATTACKING_LEFT);
						}
						break;
					}
				}

				setWalkingAnimationMode(SPEED::FAST);
				_walkingSpeed.speedLimit = _speedLimit * modifier;
			}
		}
	}
	void Player::keyReleased(Keyboard::Key key)
	{
		if (!_hit && isAlive() && !_wins)
		{
			if (key == ControlsManager::getKey(WANTED_KEY::GAMEPLAY_LEFT))
			{
				if (_gravity.onTheFloor && !actualAnimationIs(ANIMATION_STATE::ATTACKING_LEFT))
				{
					setNewAnimation(ANIMATION_STATE::IDLE_LEFT);
				}
			}
			else if (key == ControlsManager::getKey(WANTED_KEY::GAMEPLAY_RIGHT))
			{
				if (_gravity.onTheFloor && !actualAnimationIs(ANIMATION_STATE::ATTACKING_RIGHT))
				{
					setNewAnimation(ANIMATION_STATE::IDLE_RIGHT);
				}
			}
			else if (key == ControlsManager::getKey(WANTED_KEY::GAMEPLAY_ATTACK))
			{
				setWalkingAnimationMode(SPEED::NORMAL);
				_walkingSpeed.speedLimit = _speedLimit;
			}
		}
	}

	void Player::collisionWith(Floor* floor)
	{
		// Se establecen sus valores a 0 y se posiciona al personaje justo sobre el piso.
		_gravity.onTheFloor = true;
		_gravity.actualSpeed = 0.0f;

		setPosition(Vector2f(_renderer.getPosition().x, floor->getBoxCollision().getPosition().y));

		// Se establece a la animacion correspondiente.
		if (actualAnimationIs(ANIMATION_STATE::JUMPING_RIGHT))
		{
			setNewAnimation(ANIMATION_STATE::IDLE_RIGHT);
		}
		else if (actualAnimationIs(ANIMATION_STATE::JUMPING_LEFT))
		{
			setNewAnimation(ANIMATION_STATE::IDLE_LEFT);
		}
		else if (actualAnimationIs(ANIMATION_STATE::TRIPPING_RIGHT))
		{
			_animTrippingRight->resetAnimation();
			_hit = false;
			setNewAnimation(ANIMATION_STATE::IDLE_RIGHT);
		}
		else if (actualAnimationIs(ANIMATION_STATE::TRIPPING_LEFT))
		{
			_animTrippingLeft->resetAnimation();
			_hit = false;
			setNewAnimation(ANIMATION_STATE::IDLE_LEFT);
		}

		accommodateAnimations();
	}
	void Player::collisionWith(Platform* platform)
	{
		// Se establecen sus valores a 0 y se posiciona al personaje justo sobre la plataforma.
		_gravity.onTheFloor = true;
		_gravity.actualSpeed = 0.0f;

		setPosition(Vector2f(_renderer.getPosition().x, platform->getBoxCollision().getPosition().y));

		// Se establece a la animacion correspondiente.
		if (actualAnimationIs(ANIMATION_STATE::JUMPING_RIGHT))
		{
			setNewAnimation(ANIMATION_STATE::IDLE_RIGHT);
		}
		else if (actualAnimationIs(ANIMATION_STATE::JUMPING_LEFT))
		{
			setNewAnimation(ANIMATION_STATE::IDLE_LEFT);
		}
		else if (actualAnimationIs(ANIMATION_STATE::TRIPPING_RIGHT))
		{
			_animTrippingRight->resetAnimation();
			_hit = false;
			setNewAnimation(ANIMATION_STATE::IDLE_RIGHT);
		}
		else if (actualAnimationIs(ANIMATION_STATE::TRIPPING_LEFT))
		{
			_animTrippingLeft->resetAnimation();
			_hit = false;
			setNewAnimation(ANIMATION_STATE::IDLE_LEFT);
		}

		accommodateAnimations();
	}
	void Player::collisionWith(Sprite hammerItem)
	{
		_canAttack = true;
		hammerItem.setPosition(0.0f, 0.0f);
	}

	Vector2f Player::getPosition()
	{
		return _renderer.getPosition();
	}
	RectangleShape Player::getBoxCollision(BOX_COLLISION_TYPE boxCollisionType)
	{
		switch (boxCollisionType)
		{
		case BOX_COLLISION_TYPE::ENTIRE:
			return _boxEntire;
			break;

		case BOX_COLLISION_TYPE::FEET:
			return _boxFeet;
			break;

		default:
			return _boxEntire;
			break;
		}
	}
	float Player::getSpeed()
	{
		return _walkingSpeed.actualSpeed;
	}
	bool Player::getHit()
	{
		return _hit;
	}
	unsigned int Player::getLives()
	{
		return _lives;
	}
	unsigned int Player::getPoints()
	{
		return _points;
	}
	float Player::getHealth()
	{
		return _health;
	}
	float Player::getFallingSpeed()
	{
		return _gravity.actualSpeed;
	}
	StoneHammer* Player::getPlayerStoneHammer(int position)
	{
		if (position < 0 || position >= _stoneHammersSize)
		{
			return NULL;
		}
		
		return _stoneHammers[position];
	}
	int Player::getStoneHammersSize()
	{
		return _stoneHammersSize;
	}
	DIRECTION Player::getActualAnimationDirection()
	{
		if (actualAnimationIs(ANIMATION_STATE::IDLE_RIGHT) || actualAnimationIs(ANIMATION_STATE::WALKING_RIGHT) || actualAnimationIs(ANIMATION_STATE::JUMPING_RIGHT) || actualAnimationIs(ANIMATION_STATE::ATTACKING_RIGHT))
		{
			return DIRECTION::RIGHT;
		}

		return DIRECTION::LEFT;
	}
	void Player::setPosition(Vector2f position)
	{
		_renderer.setPosition(position);
		accommodateAnimations();
	}
	void Player::setNecessaryDistanceToWin(float distance)
	{
		_necessaryDistanceToWin = distance;
	}
	void Player::setAmountOfLives(unsigned int newLives)
	{
		_lives = (newLives > _maxLives) ? _maxLives : newLives;
	}
	void Player::setAmountOfPoints(unsigned int newPoints)
	{
		_points = (newPoints > _maxPoints) ? _maxPoints : newPoints;
	}

	bool Player::isAlive()
	{
		return _health > 0.0f;
	}
	bool Player::won()
	{
		return _wins;
	}
	void Player::addLife()
	{
		if (_lives < _maxLives)
		{
			_lives++;
		}
	}
	void Player::subtractLife()
	{
		if (_lives > 0)
		{
			_lives--;
		}
	}
	void Player::addHealth(float health)
	{
		_health = (_health + health > _maxHealth) ? _maxHealth : _health + health;
	}
	void Player::receiveDamage(float damage)
	{
		_health = (_health - damage > 0.0f) ? _health - damage : 0.0f;
	}
	void Player::addPoints(int points)
	{
		_points = (_points + points > _maxPoints) ? _maxPoints : _points + points;
	}

	void Player::stopWalkSpeed()
	{
		_walkingSpeed.actualSpeed = 0.0f;
	}
	void Player::tripOn(Stone* stone)
	{
		_threw = false;
		receiveDamage(stone->getDamage());

		if (isAlive())
		{
			_hit = true;
			_gravity.actualSpeed = -600.0f;

			switch (_animationState)
			{
			case ANIMATION_STATE::ATTACKING_RIGHT:
				_animAttackingRight->resetAnimation();
				break;

			case ANIMATION_STATE::ATTACKING_LEFT:
				_animAttackingLeft->resetAnimation();
				break;
			}
			switch (getActualAnimationDirection())
			{
			case DIRECTION::LEFT:
				setNewAnimation(ANIMATION_STATE::TRIPPING_LEFT);
				_walkingSpeed.actualSpeed = 750.0f;
				break;

			case DIRECTION::RIGHT:
				setNewAnimation(ANIMATION_STATE::TRIPPING_RIGHT);
				_walkingSpeed.actualSpeed = 800.0f;
				break;
			}

			accommodateAnimations();
		}
		else
		{
			lose(LOSING_TYPE::NORMAL);
			bounceWhenDies();
		}
	}
	void Player::lose(LOSING_TYPE losingType)
	{
		_health = 0.0f;

		switch (losingType)
		{
		case LOSING_TYPE::NORMAL:
			setNewAnimation(ANIMATION_STATE::LOSING_NORMAL);
			break;

		case LOSING_TYPE::BURNED:
			setNewAnimation(ANIMATION_STATE::LOSING_BURNED_1);
			break;
		}

		accommodateAnimations();

		bounceWhenDies();
	}
	void Player::winLevel()
	{
		_wins = true;
		setNewAnimation(ANIMATION_STATE::WIN);
	}
	void Player::reset()
	{
		_health = 30.0f;
		_threw = false;
		_hit = false;
		_bouncedWhenDied = false;
		_wins = false;

		_gravity.actualSpeed = 0.0f;
		_gravity.acceleration = 3750.0f;
		_gravity.speedLimit = 1000.0f;
		_gravity.onTheFloor = false;

		_walkingSpeed.actualSpeed = 0.0f;
		_walkingSpeed.acceleration = 2500.0f;
		_walkingSpeed.speedLimit = 500.0f;

		accommodateAnimations();

		setNewAnimation(ANIMATION_STATE::IDLE_RIGHT);
	}


	// Funciones privadas.
	void Player::initAnimations(float x, float y)
	{
		int left = 0; // Variable para agregar los frames a través del ancho del total de la imagen.
		int frameWidth = 0;
		int frameHeight = 0;
		float frameDuration = 0.0f;
		int amountOfFrames = 0;


		#pragma region PARADO HACIA LA DERECHA

		frameWidth = 67;
		frameHeight = 126;
		frameDuration = 0.1f;
		amountOfFrames = 2;

		if (!_texIdleRight.loadFromFile("res/sprites/player/idle_right.png"))
		{
			cout << "La textura idle_right.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texIdleRight);
		_spriteLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animIdleRight = new Animation(_spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animIdleRight->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region PARADO HACIA LA IZQUIERDA

		frameWidth = 67;
		frameHeight = 126;
		frameDuration = 0.1f;
		amountOfFrames = 2;

		if (!_texIdleLeft.loadFromFile("res/sprites/player/idle_left.png"))
		{
			cout << "La textura idle_left.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texIdleLeft);
		_spriteLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animIdleLeft = new Animation(_spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animIdleLeft->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region CAMINANDO HACIA LA DERECHA

		frameWidth = 83;
		frameHeight = 126;
		frameDuration = _walkingAnimationSpeed;
		amountOfFrames = 4;

		if (!_texWalkingRight.loadFromFile("res/sprites/player/walking_right.png"))
		{
			cout << "La textura walking_right.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texWalkingRight);
		_spriteLoader.setOrigin(frameWidth / 2.0f - 10.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animWalkingRight = new Animation(_spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animWalkingRight->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region CAMINANDO HACIA LA IZQUIERDA

		frameWidth = 83;
		frameHeight = 126;
		frameDuration = _walkingAnimationSpeed;
		amountOfFrames = 4;

		if (!_texWalkingLeft.loadFromFile("res/sprites/player/walking_left.png"))
		{
			cout << "La textura walking_left.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texWalkingLeft);
		_spriteLoader.setOrigin(frameWidth / 2.0f + 10.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animWalkingLeft = new Animation(_spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < 4; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animWalkingLeft->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region SALTANDO HACIA LA DERECHA

		frameWidth = 83;
		frameHeight = 126;
		frameDuration = 1.0f;
		amountOfFrames = 1;

		if (!_texJumpingRight.loadFromFile("res/sprites/player/jumping_right.png"))
		{
			cout << "La textura jumping_right.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texJumpingRight);
		_spriteLoader.setOrigin(frameWidth / 2.0f - 10.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animJumpingRight = new Animation(_spriteLoader, ANIMATION_MODE::ONCE);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animJumpingRight->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region SALTANDO HACIA LA IZQUIERDA

		frameWidth = 83;
		frameHeight = 126;
		frameDuration = 1.0f;
		amountOfFrames = 1;

		if (!_texJumpingLeft.loadFromFile("res/sprites/player/jumping_left.png"))
		{
			cout << "La textura jumping_left.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texJumpingLeft);
		_spriteLoader.setOrigin(frameWidth / 2.0f + 10.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animJumpingLeft = new Animation(_spriteLoader, ANIMATION_MODE::ONCE);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animJumpingLeft->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region ATACANDO HACIA LA DERECHA

		frameWidth = 116;
		frameHeight = 126;
		frameDuration = 0.1f;
		amountOfFrames = 3;

		if (!_texAttackingRight.loadFromFile("res/sprites/player/attacking_right.png"))
		{
			cout << "La textura attacking_right.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texAttackingRight);
		_spriteLoader.setOrigin(frameWidth / 2.0f - 10.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animAttackingRight = new Animation(_spriteLoader, ANIMATION_MODE::ONCE);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);

			if (i != 0)
			{
				frameDuration = 0.1125f;
			}

			Frame* frame = new Frame(intRect, frameDuration);

			_animAttackingRight->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region ATACANDO HACIA LA IZQUIERDA

		frameWidth = 116;
		frameHeight = 126;
		frameDuration = 0.1f;
		amountOfFrames = 3;

		if (!_texAttackingLeft.loadFromFile("res/sprites/player/attacking_left.png"))
		{
			cout << "La textura attacking_left.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texAttackingLeft);
		_spriteLoader.setOrigin(frameWidth / 2.0f - 10.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animAttackingLeft = new Animation(_spriteLoader, ANIMATION_MODE::ONCE);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);

			if (i != 0)
			{
				frameDuration = 0.1125f;
			}

			Frame* frame = new Frame(intRect, frameDuration);

			_animAttackingLeft->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region TROPEZÁNDOSE HACIA LA DERECHA

		frameWidth = 83;
		frameHeight = 127;
		frameDuration = 0.5f;
		amountOfFrames = 2;

		if (!_texTrippingRight.loadFromFile("res/sprites/player/tripping_right.png"))
		{
			cout << "La textura tripping_right.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texTrippingRight);
		_spriteLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animTrippingRight = new Animation(_spriteLoader, ANIMATION_MODE::ONCE);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animTrippingRight->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region TROPEZÁNDOSE HACIA LA IZQUIERDA

		frameWidth = 92;
		frameHeight = 126;
		frameDuration = 0.5f;
		amountOfFrames = 2;

		if (!_texTrippingLeft.loadFromFile("res/sprites/player/tripping_left.png"))
		{
			cout << "La textura tripping_left.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texTrippingLeft);
		_spriteLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animTrippingLeft = new Animation(_spriteLoader, ANIMATION_MODE::ONCE);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animTrippingLeft->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region PERDIENDO NORMAL

		frameWidth = 100;
		frameHeight = 128;
		frameDuration = 0.25f;
		amountOfFrames = 2;

		if (!_texLosingNormal.loadFromFile("res/sprites/player/losing_normal.png"))
		{
			cout << "La textura losing_normal.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texLosingNormal);
		_spriteLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animLosingNormal = new Animation(_spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animLosingNormal->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region PERDIENDO QUEMADO (PARTE 1)

		frameWidth = 108;
		frameHeight = 136;
		frameDuration = 0.35f;
		amountOfFrames = 2;

		if (!_texLosingBurned.loadFromFile("res/sprites/player/losing_burned.png"))
		{
			cout << "La textura losing_burned.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texLosingBurned);
		_spriteLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animLosingBurned1 = new Animation(_spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animLosingBurned1->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region PERDIENDO QUEMADO (PARTE 2)

		frameWidth = 108;
		frameHeight = 136;
		frameDuration = 0.1f;
		amountOfFrames = 2;
		left = frameWidth;

		_animLosingBurned2 = new Animation(_spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animLosingBurned2->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region FESTEJANDO

		frameWidth = 80;
		frameHeight = 128;
		frameDuration = 1.0f;
		amountOfFrames = 1;

		if (!_texWin.loadFromFile("res/sprites/player/win.png"))
		{
			cout << "La textura win.png no se ha cargado.\n";
		}
		_spriteLoader.setTexture(_texWin);
		_spriteLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		_spriteLoader.setPosition(x, y);
		_animWin = new Animation(_spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animWin->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion
	}
	void Player::updateAnimations(float deltaTime)
	{
		updateAnimationEvents();

		switch (_animationState)
		{
		case ANIMATION_STATE::IDLE_RIGHT:
			_animIdleRight->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animIdleRight->update(deltaTime);
			break;

		case ANIMATION_STATE::IDLE_LEFT:
			_animIdleLeft->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animIdleLeft->update(deltaTime);
			break;

		case ANIMATION_STATE::WALKING_RIGHT:
			_animWalkingRight->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animWalkingRight->update(deltaTime);
			break;

		case ANIMATION_STATE::WALKING_LEFT:
			_animWalkingLeft->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animWalkingLeft->update(deltaTime);
			break;

		case ANIMATION_STATE::JUMPING_RIGHT:
			_animJumpingRight->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animJumpingRight->update(deltaTime);
			break;

		case ANIMATION_STATE::JUMPING_LEFT:
			_animJumpingLeft->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animJumpingLeft->update(deltaTime);
			break;

		case ANIMATION_STATE::ATTACKING_RIGHT:
			_animAttackingRight->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animAttackingRight->update(deltaTime);
			break;

		case ANIMATION_STATE::ATTACKING_LEFT:
			_animAttackingLeft->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animAttackingLeft->update(deltaTime);
			break;

		case ANIMATION_STATE::TRIPPING_RIGHT:
			_animTrippingRight->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animTrippingRight->update(deltaTime);
			break;

		case ANIMATION_STATE::TRIPPING_LEFT:
			_animTrippingLeft->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animTrippingLeft->update(deltaTime);
			break;

		case ANIMATION_STATE::LOSING_NORMAL:
			_animLosingNormal->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animLosingNormal->update(deltaTime);
			break;

		case ANIMATION_STATE::LOSING_BURNED_1:
			_animLosingBurned1->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animLosingBurned1->update(deltaTime);
			break;

		case ANIMATION_STATE::LOSING_BURNED_2:
			_animLosingBurned2->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animLosingBurned2->update(deltaTime);
			break;

		case ANIMATION_STATE::WIN:
			_animWin->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animWin->update(deltaTime);
			break;
		}
	}
	void Player::drawAnimations(RenderWindow* window)
	{
		// Dibuja la animación correspondiente.
		switch (_animationState)
		{
		case ANIMATION_STATE::IDLE_RIGHT:
			window->draw(_animIdleRight->_target);
			break;

		case ANIMATION_STATE::IDLE_LEFT:
			window->draw(_animIdleLeft->_target);
			break;

		case ANIMATION_STATE::WALKING_RIGHT:
			window->draw(_animWalkingRight->_target);
			break;

		case ANIMATION_STATE::WALKING_LEFT:
			window->draw(_animWalkingLeft->_target);
			break;

		case ANIMATION_STATE::JUMPING_RIGHT:
			window->draw(_animJumpingRight->_target);
			break;

		case ANIMATION_STATE::JUMPING_LEFT:
			window->draw(_animJumpingLeft->_target);
			break;

		case ANIMATION_STATE::ATTACKING_RIGHT:
			window->draw(_animAttackingRight->_target);
			break;

		case ANIMATION_STATE::ATTACKING_LEFT:
			window->draw(_animAttackingLeft->_target);
			break;

		case ANIMATION_STATE::TRIPPING_RIGHT:
			window->draw(_animTrippingRight->_target);
			break;

		case ANIMATION_STATE::TRIPPING_LEFT:
			window->draw(_animTrippingLeft->_target);
			break;

		case ANIMATION_STATE::LOSING_NORMAL:
			window->draw(_animLosingNormal->_target);
			break;

		case ANIMATION_STATE::LOSING_BURNED_1:
			window->draw(_animLosingBurned1->_target);
			break;

		case ANIMATION_STATE::LOSING_BURNED_2:
			window->draw(_animLosingBurned2->_target);
			break;

		case ANIMATION_STATE::WIN:
			window->draw(_animWin->_target);
			break;
		}
	}
	void Player::accommodateAnimations()
	{
		_boxEntire.setPosition(_renderer.getPosition());
		_boxFeet.setPosition(_renderer.getPosition());
		updateAnimations(0.0f);
	}
	void Player::setWalkingAnimationMode(SPEED speed)
	{
		switch (speed)
		{
		case SPEED::NORMAL:
			for (int i = 0; i < _animWalkingRight->getAmountOfFrames(); i++)
			{
				_animWalkingRight->setDurationOfFrame(i, _walkingAnimationSpeed);
			}
			for (int i = 0; i < _animWalkingLeft->getAmountOfFrames(); i++)
			{
				_animWalkingLeft->setDurationOfFrame(i, _walkingAnimationSpeed);
			}
			break;

		case SPEED::FAST:
			float modifier = 2.5f;

			for (int i = 0; i < _animWalkingRight->getAmountOfFrames(); i++)
			{
				_animWalkingRight->setDurationOfFrame(i, _walkingAnimationSpeed / modifier);
			}
			for (int i = 0; i < _animWalkingLeft->getAmountOfFrames(); i++)
			{
				_animWalkingLeft->setDurationOfFrame(i, _walkingAnimationSpeed / modifier);
			}
			break;
		}
	}
	void Player::updateAnimationEvents()
	{
		if (_animAttackingRight->getNumberOfFrame() == 1)
		{
			if (!_threw)
			{
				attack(DIRECTION::RIGHT);
				_threw = true;
			}
		}
		else if (_animAttackingRight->getNumberOfFrame() == 2)
		{
			_animAttackingRight->resetAnimation();

			if (_gravity.onTheFloor)
			{
				setNewAnimation(ANIMATION_STATE::IDLE_RIGHT);
			}
			else
			{
				setNewAnimation(ANIMATION_STATE::JUMPING_RIGHT);
			}

			_threw = false;
		}

		if (_animAttackingLeft->getNumberOfFrame() == 1)
		{
			if (!_threw)
			{
				attack(DIRECTION::LEFT);
				_threw = true;
			}
		}
		else if (_animAttackingLeft->getNumberOfFrame() == 2)
		{
			_animAttackingLeft->resetAnimation();

			if (_gravity.onTheFloor)
			{
				setNewAnimation(ANIMATION_STATE::IDLE_LEFT);
			}
			else
			{
				setNewAnimation(ANIMATION_STATE::JUMPING_LEFT);
			}

			_threw = false;
		}

		if (_animTrippingRight->getNumberOfFrame() == 1)
		{
			_animTrippingRight->resetAnimation();
			_hit = false;

			setNewAnimation(ANIMATION_STATE::JUMPING_RIGHT);
			cout << "Fin de la animacion derecha.\n";
		}

		if (_animTrippingLeft->getNumberOfFrame() == 1)
		{
			_animTrippingLeft->resetAnimation();
			_hit = false;

			setNewAnimation(ANIMATION_STATE::JUMPING_LEFT);
		}

		if (_animLosingBurned1->getNumberOfFrame() == 1)
		{
			_animLosingBurned1->resetAnimation();

			setNewAnimation(ANIMATION_STATE::LOSING_BURNED_2);
		}
	}
	bool Player::actualAnimationIs(ANIMATION_STATE animationState)
	{
		return _animationState == animationState;
	}
	void Player::setNewAnimation(ANIMATION_STATE animationState)
	{
		_animationState = animationState;
	}

	void Player::keyPressed(float deltaTime)
	{
		if (!_hit && isAlive() && !_wins)
		{
			const float modifier = 1.25f; // Divide/multiplica la velocidad actual al estar en el aire.

			if (Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_LEFT)))
			{
				if (_gravity.onTheFloor) // Si está en el piso...
				{
					if (!Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_RIGHT)))
					{
						move(DIRECTION::LEFT, deltaTime);
						if (actualAnimationIs(ANIMATION_STATE::ATTACKING_RIGHT))
						{
							_animAttackingRight->resetAnimation();
						}
						if (!actualAnimationIs(ANIMATION_STATE::ATTACKING_LEFT))
						{
							setNewAnimation(ANIMATION_STATE::WALKING_LEFT);
						}
					}
					else
					{
						if (actualAnimationIs(ANIMATION_STATE::WALKING_LEFT))
						{
							setNewAnimation(_animationState = ANIMATION_STATE::IDLE_LEFT);
						}
					}
				}
				else // Si está en el aire...
				{
					if (!Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_RIGHT)))
					{
						if (actualAnimationIs(ANIMATION_STATE::JUMPING_RIGHT)) // Si su animación va para la derecha...
						{
							setNewAnimation(ANIMATION_STATE::JUMPING_LEFT); // Gira hacia la izquierda

							if (_walkingSpeed.actualSpeed > 0.0f) // Si su velocidad es positiva (hacia la derecha)
							{
								_walkingSpeed.actualSpeed /= modifier; // Se resta un poquito.
							}
							else if (_walkingSpeed.actualSpeed < 0.0f) // Si su velocidad es negativa (hacia la izquierda)
							{
								// Va un poco más para la izquierda, siempre y cuando no exceda su límite de velocidad.
								_walkingSpeed.actualSpeed = (_walkingSpeed.actualSpeed * modifier < -_walkingSpeed.speedLimit) ? -_walkingSpeed.speedLimit : _walkingSpeed.actualSpeed * modifier;
							}
						}
					}
				}
			}
			if (Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_RIGHT)))
			{
				if (_gravity.onTheFloor)
				{
					if (!Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_LEFT))) // Si NO está presionando izquierda...
					{
						move(DIRECTION::RIGHT, deltaTime);
						if (actualAnimationIs(ANIMATION_STATE::ATTACKING_LEFT))
						{
							_animAttackingLeft->resetAnimation();
						}
						if (!actualAnimationIs(ANIMATION_STATE::ATTACKING_RIGHT))
						{
							setNewAnimation(ANIMATION_STATE::WALKING_RIGHT);
						}
					}
					else // Si sí está presionando...
					{
						if (actualAnimationIs(ANIMATION_STATE::WALKING_RIGHT)) // Si se ve caminando hacia la derecha...
						{
							setNewAnimation(ANIMATION_STATE::IDLE_RIGHT); // Se lo ve parado.
						}
					}
				}
				else
				{
					if (!Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_LEFT)))
					{
						if (actualAnimationIs(ANIMATION_STATE::JUMPING_LEFT)) // Si su animación va para la izquierda...
						{
							setNewAnimation(ANIMATION_STATE::JUMPING_RIGHT);

							if (_walkingSpeed.actualSpeed < 0.0f) // Si su velocidad es negativa (hacia la izquierda)
							{
								_walkingSpeed.actualSpeed /= modifier; // Se resta un poquito.
							}
							else if (_walkingSpeed.actualSpeed > 0.0f) // Si su velocidad es positiva (hacia la derecha)
							{
								// Va un poco más para la derecha, siempre y cuando no exceda su límite de velocidad.
								_walkingSpeed.actualSpeed = (_walkingSpeed.actualSpeed > _walkingSpeed.actualSpeed * modifier) ? _walkingSpeed.speedLimit : _walkingSpeed.actualSpeed * modifier;
							}
						}
					}
				}
			}
		}
	}
	void Player::move(DIRECTION direction, float deltaTime)
	{
		switch (direction)
		{
		case DIRECTION::LEFT:
			_walkingSpeed.actualSpeed = (_walkingSpeed.actualSpeed - _walkingSpeed.acceleration * deltaTime > -_walkingSpeed.speedLimit) ? _walkingSpeed.actualSpeed - _walkingSpeed.acceleration * deltaTime : -_walkingSpeed.speedLimit;
			break;

		case DIRECTION::RIGHT:
			_walkingSpeed.actualSpeed = (_walkingSpeed.actualSpeed + _walkingSpeed.acceleration * deltaTime < _walkingSpeed.speedLimit) ? _walkingSpeed.actualSpeed + _walkingSpeed.acceleration * deltaTime : _walkingSpeed.speedLimit;
			break;

		default:
			_walkingSpeed.actualSpeed = 0.0f;
			break;
		}
	}
	void Player::jump(bool high)
	{
		if (high)
		{
			_gravity.actualSpeed = -_forceJump;
			_gravity.onTheFloor = false;
			cout << "Salto fuerte.\n";
		}
		else
		{
			_gravity.actualSpeed = -_forceJump / 1.25f;
			cout << "Salto debil.\n";
		}
		
		if (actualAnimationIs(ANIMATION_STATE::IDLE_RIGHT) || actualAnimationIs(ANIMATION_STATE::WALKING_RIGHT))
		{
			setNewAnimation(ANIMATION_STATE::JUMPING_RIGHT);
		}
		else if (actualAnimationIs(ANIMATION_STATE::IDLE_LEFT) || actualAnimationIs(ANIMATION_STATE::WALKING_LEFT))
		{
			setNewAnimation(ANIMATION_STATE::JUMPING_LEFT);
		}

		_gravity.onTheFloor = false;
	}
	void Player::attack(DIRECTION direction)
	{
		Vector2f distanceToCenter = { 40.0f, 110.0f };

		switch (direction)
		{
		case DIRECTION::LEFT:
			if (!_stoneHammers[_savedHammerPosition]->getIsThrown())
			{
				_stoneHammers[_savedHammerPosition]->setPosition(_renderer.getPosition().x - distanceToCenter.x, _renderer.getPosition().y - distanceToCenter.y);
			}
			break;

		case DIRECTION::RIGHT:
			if (!_stoneHammers[_savedHammerPosition]->getIsThrown())
			{
				_stoneHammers[_savedHammerPosition]->setPosition(_renderer.getPosition().x + distanceToCenter.x, _renderer.getPosition().y - distanceToCenter.y);
			}
			break;
		}

		_stoneHammers[_savedHammerPosition]->throwIt(static_cast<THROW_DIRECTION>(direction));
	}
	void Player::drainHealth(float deltaTime)
	{
		if (isAlive() && !_wins)
		{
			const float healthPerSecond = 1.0f;

			_health = (_health - healthPerSecond * deltaTime > 0.0f) ? _health - healthPerSecond * deltaTime : 0.0f;

			if (!isAlive())
			{
				lose(LOSING_TYPE::NORMAL);
			}
		}
	}
	void Player::gravityForce(float deltaTime)
	{
		if (_gravity.actualSpeed > 0.0f)
		{
			_gravity.onTheFloor = false;
		}

		_gravity.actualSpeed += _gravity.acceleration * deltaTime;

		_renderer.move(0.0f, _gravity.actualSpeed * deltaTime);
	}
	void Player::walkingAccelerationForce(float deltaTime)
	{
		if (isAlive() && !_wins)
		{
			const float multipler = 1.5f;

			// Si está sobre el piso...
			if (_gravity.onTheFloor || _hit)
			{
				// Si no está caminando para ninguno de los dos lados...
				if (bothSidesPressed() || noSidePressed() || _hit)
				{
					// Si está yendo para la derecha...
					if (_walkingSpeed.actualSpeed > 0.0f)
					{
						_walkingSpeed.actualSpeed = (_walkingSpeed.actualSpeed > _walkingSpeed.acceleration * deltaTime) ? _walkingSpeed.actualSpeed - _walkingSpeed.acceleration * deltaTime : 0.0f;
					}
					else if (_walkingSpeed.actualSpeed < 0.0f)
					{
						_walkingSpeed.actualSpeed = (_walkingSpeed.actualSpeed < -_walkingSpeed.acceleration * deltaTime) ? _walkingSpeed.actualSpeed + _walkingSpeed.acceleration * deltaTime : 0.0f;
					}
				}
			}

			//	Si está en skate...
			//		Siempre para la derecha (movimiento robótico).
			//		Si presiona izquierda, sólo va más lento. Para adelante no hace nada.

			_renderer.move(_walkingSpeed.actualSpeed * deltaTime, 0.0f);
		}
	}
	void Player::bounceWhenDies()
	{
		if (!_bouncedWhenDied)
		{
			_bouncedWhenDied = true;

			_gravity.actualSpeed = -_forceJump;
		}
	}
	void Player::checkDistanceToWin()
	{
		if (!_wins && _renderer.getPosition().x > _necessaryDistanceToWin)
		{
			winLevel();
		}
	}
	
	bool Player::bothSidesPressed()
	{
		return Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_LEFT)) && Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_RIGHT));
	}
	bool Player::noSidePressed()
	{
		return !Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_LEFT)) && !Keyboard::isKeyPressed(ControlsManager::getKey(WANTED_KEY::GAMEPLAY_RIGHT));
	}

	bool Player::isThereASavedHammer()
	{
		for (int i = 0; i < _stoneHammersSize; i++)
		{
			if (!_stoneHammers[i]->getIsThrown())
			{
				return true;
			}
		}

		return false;
	}
	int Player::saveAFreePosition()
	{
		for (int i = 0; i < _stoneHammersSize; i++)
		{
			if (!_stoneHammers[i]->getIsThrown())
			{
				return i;
			}
		}

		return -1;
	}

	void Player::updateStoneHammers(float deltaTime)
	{
		for (int i = 0; i < _stoneHammersSize; i++)
		{
			_stoneHammers[i]->update(deltaTime);
		}
	}
	void Player::drawStoneHammers(RenderWindow* window)
	{
		for (int i = 0; i < _stoneHammersSize; i++)
		{
			_stoneHammers[i]->draw(window);
		}
	}
}
