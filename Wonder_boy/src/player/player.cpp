#include "player.h"

#include <iostream>

#include "game_manager/game_manager.h"
#include "game_controls/game_controls.h"

using std::cout;


namespace the_wonder_boy
{
	Player::Player(float x, float y) : Entity(x, y)
	{
		animationState = ANIMATION_STATE::IDLE_RIGHT; // Defino con qu� sprite comienza.

		initAnimations(x, y);

		renderer.setPosition(x, y);

		gravity.actualSpeed = 0.0f;
		gravity.acceleration = 2000.0f;
		gravity.speedLimit = 1000.0f;
		gravity.onTheFloor = false;

		speedX = 500.0f;

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

	void Player::update(float deltaTime)
	{
		keyPressed(deltaTime); // Funci�n que verifica si determinadas teclas est�n siendo presionadas.
		gravityForce(deltaTime); // Aplica la fuerza gravitatoria.
		updateAnimations(deltaTime); // Actualiza las animaciones.
		accommodateAnimations();
	}
	void Player::draw(RenderWindow* window)
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
		}

		window->draw(boxEntire);
		window->draw(boxFeet);
	}
	void Player::keyPressed(float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayLeft)))
		{
			renderer.move(-speedX * deltaTime, 0.0f); // Se mueve hacia la izquierda.
			animationState = ANIMATION_STATE::IDLE_LEFT;
		}
		if (sf::Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayRight)))
		{
			renderer.move(speedX * deltaTime, 0.0f);
			animationState = ANIMATION_STATE::IDLE_RIGHT;
		}
		if (sf::Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayJump)))
		{
			if (gravity.onTheFloor)
			{
				gravity.actualSpeed = -1000;
				gravity.onTheFloor = false;
				cout << "Salta\n";
			}
		}
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
		}

		return boxEntire;
	}
	void Player::setPosition(Vector2f position)
	{
		renderer.setPosition(position);
		accommodateAnimations();
	}

	void Player::gravityForce(float deltaTime)
	{
		if (gravity.actualSpeed > 0.0f)
		{
			gravity.onTheFloor = false;
		}

		gravity.actualSpeed += gravity.acceleration * deltaTime;

		renderer.move(0.0f, gravity.actualSpeed * deltaTime);

	}
	void Player::initAnimations(float x, float y)
	{
		int left = 0; // Variable para agregar los frames a trav�s del ancho del total de la imagen.


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
}
