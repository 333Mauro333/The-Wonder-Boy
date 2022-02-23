#include "player.h"

#include <iostream>

#include "game_controls/game_controls.h"


using std::cout;


namespace the_wonder_boy
{
	Player::Player(float x, float y) : Entity(x, y)
	{
		animationState = ANIMATION_STATE::IDLE_RIGHT; // Defino con qu� sprite comienza.

		initSprites();
		initAnimations(x, y);

		renderer.setPosition(x, y);

		lost = false;
		health = 100.0f;

		gravity.actualSpeed = 0.0f;
		gravity.acceleration = 3750.0f;
		gravity.speedLimit = 1000.0f;
		gravity.onTheFloor = false;

		walkingSpeed.actualSpeed = 0.0f;
		walkingSpeed.acceleration = 2500.0f;
		walkingSpeed.speedLimit = 500.0f;

		boxEntire.setFillColor(sf::Color(255, 0, 0, 128));
		boxEntire.setSize(Vector2f(67, 126));
		boxEntire.setOrigin(Vector2f(33, 126));

		boxFeet.setFillColor(sf::Color(255, 0, 0, 128));
		boxFeet.setSize(Vector2f(67, 20));
		boxFeet.setOrigin(Vector2f(33, 20));

		for (int i = 0; i < stoneHammersSize; i++)
		{
			stoneHammers[i] = new StoneHammer();
		}

		savedHammerPosition = -1;

		cout << "Se ha creado un jugador.\n\n";
	}
	Player::~Player()
	{
		delete animIdleLeft;
		delete animIdleRight;
		delete animWalkingLeft;
		delete animWalkingRight;
		delete animJumpingLeft;
		delete animJumpingRight;

		cout << "El jugador ha sido eliminado de la memoria.\n";
	}


	// Funciones p�blicas.
	void Player::update(float deltaTime)
	{
		keyPressed(deltaTime); // Funci�n que verifica si determinadas teclas est�n siendo presionadas.
		gravityForce(deltaTime); // Aplica la fuerza gravitatoria.
		walkingAccelerationForce(deltaTime); // Aplica la velocidad al caminar.
		updateAnimations(deltaTime); // Actualiza las animaciones.
		accommodateAnimations(); // Acomoda las animaciones a la posici�n del sprite central.
		updateStoneHammers(deltaTime);
	}
	void Player::draw(RenderWindow* window)
	{
		drawAnimations(window);
		drawStoneHammers(window);

		// Dibujado de las cajas de colisiones.
		#if _DEBUG

		window->draw(boxEntire);
		window->draw(boxFeet);

		#endif // _DEBUG
	}
	void Player::keyPressedOnce(Keyboard::Key key)
	{
		if (!lost)
		{
			if (key == GameControls::gameplayJump)
			{
				if (gravity.onTheFloor) // Si est� en el piso...
				{
					// Orden de verificaciones:
					// 1. Si la tecla de ataque est� siendo presionada. Si es as�, salta alto.
					// 2. Eval�a las siguientes 2 condiciones para que pueda:
						// a. Que no est� presionando ambos lados a la vez.
						// b. Que est� presionando alguno.
					bool high = Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayAttack)) ||
						!bothSidesPressed() &&
						(Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayLeft)) ||
							Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayRight)));

					jump(high);
				}
			}
			if (key == GameControls::gameplayAttack)
			{
				const float modifier = 1.5f;


				switch (animationState)
				{
				case ANIMATION_STATE::IDLE_RIGHT:
				case ANIMATION_STATE::WALKING_RIGHT:
				case ANIMATION_STATE::JUMPING_RIGHT:
					if (isThereASavedHammer())
					{
						savedHammerPosition = saveAFreePosition();
						setNewAnimation(ANIMATION_STATE::ATTACKING_RIGHT);
					}
					break;

				case ANIMATION_STATE::IDLE_LEFT:
				case ANIMATION_STATE::WALKING_LEFT:
				case ANIMATION_STATE::JUMPING_LEFT:
					if (isThereASavedHammer())
					{
						savedHammerPosition = saveAFreePosition();
						setNewAnimation(ANIMATION_STATE::ATTACKING_LEFT);
					}
					break;
				}

				setWalkingAnimationMode(SPEED::FAST);
				walkingSpeed.speedLimit = speedLimit * modifier;
			}
		}
	}
	void Player::keyReleased(Keyboard::Key key)
	{
		if (!lost)
		{
			if (key == GameControls::gameplayLeft)
			{
				if (gravity.onTheFloor && !actualAnimationIs(ANIMATION_STATE::ATTACKING_LEFT))
				{
					setNewAnimation(ANIMATION_STATE::IDLE_LEFT);
				}
			}
			if (key == GameControls::gameplayRight)
			{
				if (gravity.onTheFloor && !actualAnimationIs(ANIMATION_STATE::ATTACKING_RIGHT))
				{
					setNewAnimation(ANIMATION_STATE::IDLE_RIGHT);
				}
			}
			if (key == GameControls::gameplayAttack)
			{
				setWalkingAnimationMode(SPEED::NORMAL);
				walkingSpeed.speedLimit = speedLimit;
			}
		}
	}

	void Player::collisionWith(Floor* floor)
	{
		// Se establecen sus valores a 0 y se posiciona al personaje justo sobre el piso.
		gravity.onTheFloor = true;
		gravity.actualSpeed = 0.0f;

		setPosition(Vector2f(renderer.getPosition().x, floor->getBoxCollision().getPosition().y));

		// Se establece a la animacion correspondiente.
		if (actualAnimationIs(ANIMATION_STATE::JUMPING_RIGHT))
		{
			setNewAnimation(ANIMATION_STATE::IDLE_RIGHT);
		}
		else if (actualAnimationIs(ANIMATION_STATE::JUMPING_LEFT))
		{
			setNewAnimation(ANIMATION_STATE::IDLE_LEFT);
		}
		accommodateAnimations();
	}

	Vector2f Player::getPosition()
	{
		return renderer.getPosition();
	}
	RectangleShape Player::getBoxCollision(BOX_COLLISION_TYPE boxCollisionType)
	{
		switch (boxCollisionType)
		{
		case BOX_COLLISION_TYPE::ENTIRE:
			return boxEntire;
			break;

		case BOX_COLLISION_TYPE::FEET:
			return boxFeet;
			break;

		default:
			return boxEntire;
			break;
		}
	}
	Sprite Player::getLifeSprite()
	{
		return sprLife;
	}
	Sprite Player::getExtraLifeSprite()
	{
		return sprExtraLife;
	}
	float Player::getSpeed()
	{
		return walkingSpeed.actualSpeed;
	}
	float Player::getHealth()
	{
		return health;
	}
	float Player::getFallingSpeed()
	{
		return gravity.actualSpeed;
	}
	StoneHammer* Player::getPlayerStoneHammer(int position)
	{
		if (position < 0 || position >= stoneHammersSize)
		{
			return NULL;
		}
		
		return stoneHammers[position];
	}
	int Player::getStoneHammersSize()
	{
		return stoneHammersSize;
	}
	void Player::setPosition(Vector2f position)
	{
		renderer.setPosition(position);
		accommodateAnimations();
	}
	void Player::setLost(bool lost)
	{
		this->lost = lost;
	}
	void Player::stopWalkSpeed()
	{
		walkingSpeed.actualSpeed = 0.0f;
	}
	void Player::addHealth(float health)
	{
		const float maxHealth = 100.0f;


		this->health = (this->health + health > maxHealth) ? maxHealth : this->health + health;
	}


	// Funciones privadas.
	void Player::initSprites()
	{
		if (!texLife.loadFromFile("res/sprites/player/life.png"))
		{
			cout << "La textura life.png no se ha cargado.\n";
		}
		sprLife.setTexture(texLife);

		if (!texExtraLife.loadFromFile("res/sprites/player/extra_life.png"))
		{
			cout << "La textura extra_life.png no se ha cargado.\n";
		}
		sprExtraLife.setTexture(texExtraLife);
	}
	void Player::initAnimations(float x, float y)
	{
		int left = 0; // Variable para agregar los frames a trav�s del ancho del total de la imagen.
		int frameWidth = 0;
		int frameHeight = 0;
		float frameDuration = 0.0f;
		int amountOfFrames = 0;


		#pragma region PARADO HACIA LA DERECHA

		frameWidth = 67;
		frameHeight = 126;
		frameDuration = 0.1f;
		amountOfFrames = 2;

		if (!texIdleRight.loadFromFile("res/sprites/player/idle_right.png"))
		{
			cout << "La textura idle_right.png no se ha cargado.\n";
		}
		spriteLoader.setTexture(texIdleRight);
		spriteLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		spriteLoader.setPosition(x, y);
		animIdleRight = new Animation(spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			animIdleRight->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region PARADO HACIA LA IZQUIERDA

		frameWidth = 67;
		frameHeight = 126;
		frameDuration = 0.1f;
		amountOfFrames = 2;

		if (!texIdleLeft.loadFromFile("res/sprites/player/idle_left.png"))
		{
			cout << "La textura idle_left.png no se ha cargado.\n";
		}
		spriteLoader.setTexture(texIdleLeft);
		spriteLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		spriteLoader.setPosition(x, y);
		animIdleLeft = new Animation(spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			animIdleLeft->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region CAMINANDO HACIA LA DERECHA

		frameWidth = 83;
		frameHeight = 126;
		frameDuration = walkingAnimationSpeed;
		amountOfFrames = 4;

		if (!texWalkingRight.loadFromFile("res/sprites/player/walking_right.png"))
		{
			cout << "La textura walking_right.png no se ha cargado.\n";
		}
		spriteLoader.setTexture(texWalkingRight);
		spriteLoader.setOrigin(frameWidth / 2.0f - 10.0f, static_cast<float>(frameHeight));
		spriteLoader.setPosition(x, y);
		animWalkingRight = new Animation(spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			animWalkingRight->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region CAMINANDO HACIA LA IZQUIERDA

		frameWidth = 83;
		frameHeight = 126;
		frameDuration = walkingAnimationSpeed;
		amountOfFrames = 4;

		if (!texWalkingLeft.loadFromFile("res/sprites/player/walking_left.png"))
		{
			cout << "La textura walking_left.png no se ha cargado.\n";
		}
		spriteLoader.setTexture(texWalkingLeft);
		spriteLoader.setOrigin(frameWidth / 2.0f + 10.0f, static_cast<float>(frameHeight));
		spriteLoader.setPosition(x, y);
		animWalkingLeft = new Animation(spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < 4; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			animWalkingLeft->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region SALTANDO HACIA LA DERECHA

		frameWidth = 83;
		frameHeight = 126;
		frameDuration = 1.0f;
		amountOfFrames = 1;

		if (!texJumpingRight.loadFromFile("res/sprites/player/jumping_right.png"))
		{
			cout << "La textura jumping_right.png no se ha cargado.\n";
		}
		spriteLoader.setTexture(texJumpingRight);
		spriteLoader.setOrigin(frameWidth / 2.0f - 10.0f, static_cast<float>(frameHeight));
		spriteLoader.setPosition(x, y);
		animJumpingRight = new Animation(spriteLoader, ANIMATION_MODE::ONCE);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			animJumpingRight->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region SALTANDO HACIA LA IZQUIERDA

		frameWidth = 83;
		frameHeight = 126;
		frameDuration = 1.0f;
		amountOfFrames = 1;

		if (!texJumpingLeft.loadFromFile("res/sprites/player/jumping_left.png"))
		{
			cout << "La textura jumping_left.png no se ha cargado.\n";
		}
		spriteLoader.setTexture(texJumpingLeft);
		spriteLoader.setOrigin(frameWidth / 2.0f + 10.0f, static_cast<float>(frameHeight));
		spriteLoader.setPosition(x, y);
		animJumpingLeft = new Animation(spriteLoader, ANIMATION_MODE::ONCE);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			animJumpingLeft->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region ATACANDO HACIA LA DERECHA

		frameWidth = 116;
		frameHeight = 126;
		frameDuration = 0.1f;
		amountOfFrames = 3;

		if (!texAttackingRight.loadFromFile("res/sprites/player/attacking_right.png"))
		{
			cout << "La textura attacking_right.png no se ha cargado.\n";
		}
		spriteLoader.setTexture(texAttackingRight);
		spriteLoader.setOrigin(frameWidth / 2.0f - 10.0f, static_cast<float>(frameHeight));
		spriteLoader.setPosition(x, y);
		animAttackingRight = new Animation(spriteLoader, ANIMATION_MODE::ONCE);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);

			if (i != 0)
			{
				frameDuration = 0.125f;
			}

			Frame* frame = new Frame(intRect, frameDuration);

			animAttackingRight->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region ATACANDO HACIA LA IZQUIERDA

		frameWidth = 116;
		frameHeight = 126;
		frameDuration = 0.1f;
		amountOfFrames = 3;

		if (!texAttackingLeft.loadFromFile("res/sprites/player/attacking_left.png"))
		{
			cout << "La textura attacking_left.png no se ha cargado.\n";
		}
		spriteLoader.setTexture(texAttackingLeft);
		spriteLoader.setOrigin(frameWidth / 2.0f - 10.0f, static_cast<float>(frameHeight));
		spriteLoader.setPosition(x, y);
		animAttackingLeft = new Animation(spriteLoader, ANIMATION_MODE::ONCE);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);

			if (i != 0)
			{
				frameDuration = 0.125f;
			}

			Frame* frame = new Frame(intRect, frameDuration);

			animAttackingLeft->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion
	}
	void Player::updateAnimations(float deltaTime)
	{
		updateAnimationEvents();

		switch (animationState)
		{
		case ANIMATION_STATE::IDLE_RIGHT:
			animIdleRight->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
			animIdleRight->update(deltaTime);
			break;

		case ANIMATION_STATE::IDLE_LEFT:
			animIdleLeft->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
			animIdleLeft->update(deltaTime);
			break;

		case ANIMATION_STATE::WALKING_RIGHT:
			animWalkingRight->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
			animWalkingRight->update(deltaTime);
			break;

		case ANIMATION_STATE::WALKING_LEFT:
			animWalkingLeft->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
			animWalkingLeft->update(deltaTime);
			break;

		case ANIMATION_STATE::JUMPING_RIGHT:
			animJumpingRight->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
			animJumpingRight->update(deltaTime);
			break;

		case ANIMATION_STATE::JUMPING_LEFT:
			animJumpingLeft->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
			animJumpingLeft->update(deltaTime);
			break;

		case ANIMATION_STATE::ATTACKING_RIGHT:
			animAttackingRight->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
			animAttackingRight->update(deltaTime);
			break;

		case ANIMATION_STATE::ATTACKING_LEFT:
			animAttackingLeft->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
			animAttackingLeft->update(deltaTime);
			break;
		}
	}
	void Player::drawAnimations(RenderWindow* window)
	{
		// Dibuja la animaci�n correspondiente.
		switch (animationState)
		{
		case ANIMATION_STATE::IDLE_RIGHT:
			window->draw(animIdleRight->target);
			break;

		case ANIMATION_STATE::IDLE_LEFT:
			window->draw(animIdleLeft->target);
			break;

		case ANIMATION_STATE::WALKING_RIGHT:
			window->draw(animWalkingRight->target);
			break;

		case ANIMATION_STATE::WALKING_LEFT:
			window->draw(animWalkingLeft->target);
			break;

		case ANIMATION_STATE::JUMPING_RIGHT:
			window->draw(animJumpingRight->target);
			break;

		case ANIMATION_STATE::JUMPING_LEFT:
			window->draw(animJumpingLeft->target);
			break;

		case ANIMATION_STATE::ATTACKING_RIGHT:
			window->draw(animAttackingRight->target);
			break;

		case ANIMATION_STATE::ATTACKING_LEFT:
			window->draw(animAttackingLeft->target);
			break;
		}
	}
	void Player::accommodateAnimations()
	{
		boxEntire.setPosition(renderer.getPosition());
		boxFeet.setPosition(renderer.getPosition());
		updateAnimations(0.0f);
	}
	void Player::setWalkingAnimationMode(SPEED speed)
	{
		switch (speed)
		{
		case SPEED::NORMAL:
			for (int i = 0; i < animWalkingRight->getAmountOfFrames(); i++)
			{
				animWalkingRight->setDurationOfFrame(i, walkingAnimationSpeed);
			}
			for (int i = 0; i < animWalkingLeft->getAmountOfFrames(); i++)
			{
				animWalkingLeft->setDurationOfFrame(i, walkingAnimationSpeed);
			}
			break;

		case SPEED::FAST:
			float modifier = 2.5f;

			for (int i = 0; i < animWalkingRight->getAmountOfFrames(); i++)
			{
				animWalkingRight->setDurationOfFrame(i, walkingAnimationSpeed / modifier);
			}
			for (int i = 0; i < animWalkingLeft->getAmountOfFrames(); i++)
			{
				animWalkingLeft->setDurationOfFrame(i, walkingAnimationSpeed / modifier);
			}
			break;
		}
	}
	void Player::updateAnimationEvents()
	{
		if (animAttackingRight->getNumberOfFrame() == 1)
		{
			attack(DIRECTION::RIGHT);
		}
		else if (animAttackingRight->getNumberOfFrame() == 2)
		{
			animAttackingRight->resetAnimation();

			if (gravity.onTheFloor)
			{
				setNewAnimation(ANIMATION_STATE::IDLE_RIGHT);
			}
			else
			{
				setNewAnimation(ANIMATION_STATE::JUMPING_RIGHT);
			}
		}

		if (animAttackingLeft->getNumberOfFrame() == 1)
		{
			attack(DIRECTION::LEFT);
		}
		else if (animAttackingLeft->getNumberOfFrame() == 2)
		{
			animAttackingLeft->resetAnimation();

			if (gravity.onTheFloor)
			{
				setNewAnimation(ANIMATION_STATE::IDLE_LEFT);
			}
			else
			{
				setNewAnimation(ANIMATION_STATE::JUMPING_LEFT);
			}
		}
	}
	bool Player::actualAnimationIs(ANIMATION_STATE animation)
	{
		return animationState == animation;
	}
	void Player::setNewAnimation(ANIMATION_STATE animation)
	{
		animationState = animation;
	}

	void Player::keyPressed(float deltaTime)
	{
		if (!lost)
		{
			const float modifier = 1.25f; // Divide/multiplica la velocidad actual al estar en el aire.


			if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayLeft)))
			{
				if (gravity.onTheFloor) // Si est� en el piso...
				{
					if (!Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayRight)))
					{
						move(DIRECTION::LEFT, deltaTime);
						if (actualAnimationIs(ANIMATION_STATE::ATTACKING_RIGHT))
						{
							animAttackingRight->resetAnimation();
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
							setNewAnimation(animationState = ANIMATION_STATE::IDLE_LEFT);
						}
					}
				}
				else // Si est� en el aire...
				{
					if (!Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayRight)))
					{
						if (actualAnimationIs(ANIMATION_STATE::JUMPING_RIGHT)) // Si su animaci�n va para la derecha...
						{
							setNewAnimation(ANIMATION_STATE::JUMPING_LEFT); // Gira hacia la izquierda

							if (walkingSpeed.actualSpeed > 0.0f) // Si su velocidad es positiva (hacia la derecha)
							{
								walkingSpeed.actualSpeed /= modifier; // Se resta un poquito.
							}
							else if (walkingSpeed.actualSpeed < 0.0f) // Si su velocidad es negativa (hacia la izquierda)
							{
								// Va un poco m�s para la izquierda, siempre y cuando no exceda su l�mite de velocidad.
								walkingSpeed.actualSpeed = (walkingSpeed.actualSpeed * modifier < -walkingSpeed.speedLimit) ? -walkingSpeed.speedLimit : walkingSpeed.actualSpeed * modifier;
							}
						}
					}
				}
			}
			if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayRight)))
			{
				if (gravity.onTheFloor)
				{
					if (!Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayLeft))) // Si NO est� presionando izquierda...
					{
						move(DIRECTION::RIGHT, deltaTime);
						if (actualAnimationIs(ANIMATION_STATE::ATTACKING_LEFT))
						{
							animAttackingLeft->resetAnimation();
						}
						if (!actualAnimationIs(ANIMATION_STATE::ATTACKING_RIGHT))
						{
							setNewAnimation(ANIMATION_STATE::WALKING_RIGHT);
						}
					}
					else // Si s� est� presionando...
					{
						if (actualAnimationIs(ANIMATION_STATE::WALKING_RIGHT)) // Si se ve caminando hacia la derecha...
						{
							setNewAnimation(ANIMATION_STATE::IDLE_RIGHT); // Se lo ve parado.
						}
					}
				}
				else
				{
					if (!Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayLeft)))
					{
						if (actualAnimationIs(ANIMATION_STATE::JUMPING_LEFT)) // Si su animaci�n va para la izquierda...
						{
							setNewAnimation(ANIMATION_STATE::JUMPING_RIGHT);

							if (walkingSpeed.actualSpeed < 0.0f) // Si su velocidad es negativa (hacia la izquierda)
							{
								walkingSpeed.actualSpeed /= modifier; // Se resta un poquito.
							}
							else if (walkingSpeed.actualSpeed > 0.0f) // Si su velocidad es positiva (hacia la derecha)
							{
								// Va un poco m�s para la derecha, siempre y cuando no exceda su l�mite de velocidad.
								walkingSpeed.actualSpeed = (walkingSpeed.actualSpeed > walkingSpeed.actualSpeed * modifier) ? walkingSpeed.speedLimit : walkingSpeed.actualSpeed * modifier;
							}
						}
					}
				}
			}
		}

		cout << "Velocidad del player: " << walkingSpeed.actualSpeed << std::endl;
	}
	void Player::move(DIRECTION direction, float deltaTime)
	{
		switch (direction)
		{
		case DIRECTION::LEFT:
			walkingSpeed.actualSpeed = (walkingSpeed.actualSpeed - walkingSpeed.acceleration * deltaTime > -walkingSpeed.speedLimit) ? walkingSpeed.actualSpeed - walkingSpeed.acceleration * deltaTime : -walkingSpeed.speedLimit;
			break;

		case DIRECTION::RIGHT:
			walkingSpeed.actualSpeed = (walkingSpeed.actualSpeed + walkingSpeed.acceleration * deltaTime < walkingSpeed.speedLimit) ? walkingSpeed.actualSpeed + walkingSpeed.acceleration * deltaTime : walkingSpeed.speedLimit;
			break;

		default:
			walkingSpeed.actualSpeed = 0.0f;
			break;
		}
	}
	void Player::jump(bool high)
	{
		if (high)
		{
			gravity.actualSpeed = -forceJump;
			gravity.onTheFloor = false;
			cout << "Salto fuerte.\n";
		}
		else
		{
			gravity.actualSpeed = -forceJump / 1.25f;
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

		gravity.onTheFloor = false;
	}
	void Player::attack(DIRECTION direction)
	{
		switch (direction)
		{
		case DIRECTION::LEFT:
			if (!stoneHammers[savedHammerPosition]->getIsThrown())
			{
				stoneHammers[savedHammerPosition]->setPosition(renderer.getPosition().x - 20.0f, renderer.getPosition().y - 80.0f);
			}
			break;

		case DIRECTION::RIGHT:
			if (!stoneHammers[savedHammerPosition]->getIsThrown())
			{
				stoneHammers[savedHammerPosition]->setPosition(renderer.getPosition().x + 20.0f, renderer.getPosition().y - 80.0f);
			}
			break;
		}

		stoneHammers[savedHammerPosition]->throwIt(static_cast<THROW_DIRECTION>(direction));
	}
	void Player::gravityForce(float deltaTime)
	{
		if (!lost)
		{
			if (gravity.actualSpeed > 0.0f)
			{
				gravity.onTheFloor = false;
			}

			gravity.actualSpeed += gravity.acceleration * deltaTime;

			renderer.move(0.0f, gravity.actualSpeed * deltaTime);
		}
	}
	void Player::walkingAccelerationForce(float deltaTime)
	{
		if (!lost)
		{
			const float multipler = 1.5f;

			// Si est� sobre el piso...
			if (gravity.onTheFloor)
			{
				// Si no est� caminando para ninguno de los dos lados...
				if (bothSidesPressed() || noSidePressed())
				{
					// Si est� yendo para la derecha...
					if (walkingSpeed.actualSpeed > 0.0f)
					{
						walkingSpeed.actualSpeed = (walkingSpeed.actualSpeed > walkingSpeed.acceleration * deltaTime) ? walkingSpeed.actualSpeed - walkingSpeed.acceleration * deltaTime : 0.0f;
					}
					else if (walkingSpeed.actualSpeed < 0.0f)
					{
						walkingSpeed.actualSpeed = (walkingSpeed.actualSpeed < -walkingSpeed.acceleration * deltaTime) ? walkingSpeed.actualSpeed + walkingSpeed.acceleration * deltaTime : 0.0f;
					}
				}
			}

			//	Si est� en skate...
			//		Siempre para la derecha (movimiento rob�tico).
			//		Si presiona izquierda, s�lo va m�s lento. Para adelante no hace nada.

			renderer.move(walkingSpeed.actualSpeed * deltaTime, 0.0f);
		}
	}
	
	bool Player::bothSidesPressed()
	{
		return Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayLeft)) && Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayRight));
	}
	bool Player::noSidePressed()
	{
		return !Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayLeft)) && !Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayRight));
	}

	bool Player::isThereASavedHammer()
	{
		for (int i = 0; i < stoneHammersSize; i++)
		{
			if (!stoneHammers[i]->getIsThrown())
			{
				return true;
			}
		}

		return false;
	}
	int Player::saveAFreePosition()
	{
		for (int i = 0; i < stoneHammersSize; i++)
		{
			if (!stoneHammers[i]->getIsThrown())
			{
				return i;
			}
		}

		return -1;
	}

	void Player::updateStoneHammers(float deltaTime)
	{
		for (int i = 0; i < stoneHammersSize; i++)
		{
			stoneHammers[i]->update(deltaTime);
		}
	}
	void Player::drawStoneHammers(RenderWindow* window)
	{
		for (int i = 0; i < stoneHammersSize; i++)
		{
			stoneHammers[i]->draw(window);
		}
	}
}
