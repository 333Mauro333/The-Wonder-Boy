#include "player.h"

#include <iostream>

#include "game_manager/game_manager.h"
#include "game_controls/game_controls.h"

using std::cout;
using sf::Keyboard;


namespace the_wonder_boy
{
	Player::Player(float x, float y) : Entity(x, y)
	{
		animationState = ANIMATION_STATE::IDLE_RIGHT; // Defino con qué sprite comienza.

		initAnimations(x, y);

		renderer.setPosition(x, y);

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

		cout << "Se ha creado un jugador.\n\n";
	}
	Player::~Player()
	{
		delete animIdleLeft;
		delete animIdleRight;

		cout << "El jugador ha sido eliminado de la memoria.\n";
	}

	// Funciones públicas.
	void Player::update(float deltaTime)
	{
		keyPressed(deltaTime); // Función que verifica si determinadas teclas están siendo presionadas.
		gravityForce(deltaTime); // Aplica la fuerza gravitatoria.
		walkingAccelerationForce(deltaTime); // Aplica la velocidad al caminar.
		updateAnimations(deltaTime); // Actualiza las animaciones.
		accommodateAnimations(); // Acomoda las animaciones a la posición del sprite central.
	}
	void Player::draw(RenderWindow* window)
	{
		// Dibuja la animación correspondiente.
		switch (animationState)
		{
		case ANIMATION_STATE::IDLE_RIGHT:
			window->draw(animIdleRight->target);
			break;

		case ANIMATION_STATE::IDLE_LEFT:
			window->draw(animIdleLeft->target);
			break;
		}

		// Dibujado de las cajas de colisiones.
		#if _DEBUG

		window->draw(boxEntire);
		window->draw(boxFeet);

		#endif // _DEBUG
	}
	void Player::keyPressed(float deltaTime)
	{
		const float modifier = 1.25f; // Divide/multiplica la velocidad actual al estar en el aire.


		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayLeft)))
		{
			if (gravity.onTheFloor) // Si está en el piso...
			{
				move(DIRECTION::LEFT, deltaTime);
				animationState = ANIMATION_STATE::IDLE_LEFT;
			}
			else // Si está en el aire...
			{
				if (animationState == ANIMATION_STATE::IDLE_RIGHT) // Si su animación va para la derecha...
				{
					animationState = ANIMATION_STATE::IDLE_LEFT; // Gira hacia la izquierda

					if (walkingSpeed.actualSpeed > 0.0f) // Si su velocidad es positiva (hacia la derecha)
					{
						walkingSpeed.actualSpeed /= modifier; // Se resta un poquito.
					}
					else if (walkingSpeed.actualSpeed < 0.0f) // Si su velocidad es negativa (hacia la izquierda)
					{
						// Va un poco más para la izquierda, siempre y cuando no exceda su límite de velocidad.
						walkingSpeed.actualSpeed = (walkingSpeed.actualSpeed * modifier < -walkingSpeed.speedLimit) ? -walkingSpeed.speedLimit : walkingSpeed.actualSpeed * modifier;
					}
				}
			}
		}
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayRight)))
		{
			if (gravity.onTheFloor)
			{
				move(DIRECTION::RIGHT, deltaTime);
				animationState = ANIMATION_STATE::IDLE_RIGHT;
			}
			else
			{
				if (animationState == ANIMATION_STATE::IDLE_LEFT) // Si su animación va para la izquierda...
				{
					animationState = ANIMATION_STATE::IDLE_RIGHT;

					if (walkingSpeed.actualSpeed < 0.0f) // Si su velocidad es negativa (hacia la izquierda)
					{
						walkingSpeed.actualSpeed /= modifier; // Se resta un poquito.
					}
					else if (walkingSpeed.actualSpeed > 0.0f) // Si su velocidad es positiva (hacia la derecha)
					{
						// Va un poco más para la derecha, siempre y cuando no exceda su límite de velocidad.
						walkingSpeed.actualSpeed = (walkingSpeed.actualSpeed > walkingSpeed.actualSpeed * modifier) ? walkingSpeed.speedLimit : walkingSpeed.actualSpeed * modifier;
					}
				}
			}
		}

		cout << "Velocidad del player: " << walkingSpeed.actualSpeed << std::endl;
	}
	bool Player::isCollidingWith(Floor* floor)
	{
		return	boxFeet.getPosition().y > floor->getRenderer().getPosition().y - floor->getRenderer().getGlobalBounds().height / 2.0f &&
			boxFeet.getPosition().y - boxFeet.getSize().y < floor->getRenderer().getPosition().y + floor->getRenderer().getGlobalBounds().height / 2.0f &&
			boxFeet.getPosition().x + boxFeet.getSize().x / 2.0f > floor->getRenderer().getPosition().x - floor->getRenderer().getGlobalBounds().width / 2.0f &&
			boxFeet.getPosition().x - boxFeet.getSize().x / 2.0f < floor->getRenderer().getPosition().x + floor->getRenderer().getGlobalBounds().width / 2.0f;
	}
	void Player::collisionWith(Floor* floor)
	{
		// Se establecen sus valores a 0 y se posiciona al personaje justo sobre el piso.
		gravity.onTheFloor = true;
		gravity.actualSpeed = 0.0f;
		setPosition(Vector2f(renderer.getPosition().x, floor->getRenderer().getPosition().y - floor->getRenderer().getGlobalBounds().height / 2.0f));
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
	void Player::setPosition(Vector2f position)
	{
		renderer.setPosition(position);
		accommodateAnimations();
	}
	void Player::keyPressedOnce(Keyboard::Key key)
	{
		if (key == GameControls::gameplayJump)
		{
			if (gravity.onTheFloor) // Si está en el piso...
			{
				// Verifica si alguna de las teclas (IZQ, DER o ATTACK) se están presionando. Si es así, salta alto.
				bool high = Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayRight)) ||
					Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayAttack)) ||
					Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayLeft));

				jump(high);
			}
		}
	}

	// Funciones privadas.
	void Player::gravityForce(float deltaTime)
	{
		if (gravity.actualSpeed > 0.0f)
		{
			gravity.onTheFloor = false;
		}

		gravity.actualSpeed += gravity.acceleration * deltaTime;

		renderer.move(0.0f, gravity.actualSpeed * deltaTime);

	}
	void Player::walkingAccelerationForce(float deltaTime)
	{
		const float multipler = 1.5f;

		// Si no está caminando para ninguno de los dos lados...
		if (gravity.onTheFloor && !Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayLeft)) && !Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayRight)))
		{
			// Si está yendo para la derecha...
			if (walkingSpeed.actualSpeed > 0.0f)
			{
				walkingSpeed.actualSpeed = (walkingSpeed.actualSpeed > walkingSpeed.acceleration * deltaTime) ? walkingSpeed.actualSpeed - walkingSpeed.acceleration * deltaTime : 0.0f;
			}
			else if (walkingSpeed.actualSpeed < 0.0f)
			{
				walkingSpeed.actualSpeed = (walkingSpeed.actualSpeed < -walkingSpeed.acceleration * deltaTime) ? walkingSpeed.actualSpeed + walkingSpeed.acceleration * deltaTime : 0.0f;
			}

		}
		renderer.move(walkingSpeed.actualSpeed * deltaTime, 0.0f);
		//	Si está a pie...
		//		Si no está caminando para ninguno de los dos lados, baja a cero.
		//		Si está en el aire, no aplica.
		//	Si está en skate...
		//		Siempre para la derecha (movimiento robótico).
		//		Si presiona izquierda, sólo va más lento. Para adelante no hace nada.
	}
	void Player::initAnimations(float x, float y)
	{
		int left = 0; // Variable para agregar los frames a través del ancho del total de la imagen.


		#pragma region PARADO HACIA LA DERECHA

		if (!texIdleRight.loadFromFile("res/sprites/player/idle_right.png"))
		{
			cout << "La textura idle_right.png no se ha cargado.\n";
		}
		spriteLoader.setTexture(texIdleRight);
		spriteLoader.setOrigin(33, 126);
		spriteLoader.setPosition(x, y);
		animIdleRight = new Animation(spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < 2; i++)
		{
			IntRect intRect = IntRect(left, 0, 67, 126);
			Frame* frame = new Frame(intRect, 0.1f);

			animIdleRight->addFrame(frame);
			left += 67;
		}
		left = 0;

		#pragma endregion

		#pragma region PARADO HACIA LA IZQUIERDA

		if (!texIdleLeft.loadFromFile("res/sprites/player/idle_left.png"))
		{
			cout << "La textura idle_left.png no se ha cargado.\n";
		}
		spriteLoader.setTexture(texIdleLeft);
		spriteLoader.setOrigin(33, 126);
		spriteLoader.setPosition(x, y);
		animIdleLeft = new Animation(spriteLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < 2; i++)
		{
			IntRect intRect = IntRect(left, 0, 67, 126);
			Frame* frame = new Frame(intRect, 0.1f);

			animIdleLeft->addFrame(frame);
			left += 67;
		}
		left = 0;

		#pragma endregion
	}
	void Player::updateAnimations(float deltaTime)
	{
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
		}
	}
	void Player::accommodateAnimations()
	{
		boxEntire.setPosition(renderer.getPosition());
		boxFeet.setPosition(renderer.getPosition());
		updateAnimations(0.0f);
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
		const float forceJump = 1400.0f;


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

		gravity.onTheFloor = false;
	}
}
