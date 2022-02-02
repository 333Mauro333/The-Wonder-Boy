#include "player.h"

#include <iostream>

#include "game_manager/game_manager.h"
#include "game_controls/game_controls.h"

using std::cout;


namespace the_wonder_boy
{
	Player::Player(float x, float y) : Entity(x, y)
	{
		animationState = ANIMATION_STATE::IDLE_RIGHT;

		initAnimations(x, y);

		switch (animationState)
		{
		case ANIMATION_STATE::IDLE_RIGHT:
			break;

		case ANIMATION_STATE::IDLE_LEFT:
			break;

		default:
			break;
		}

		renderer.setPosition(x, y);

		gravity.actualSpeed = 0.0f;
		gravity.acceleration = 2000.0f;
		gravity.speedLimit = 1000.0f;
		gravity.onTheFloor = false;

		speedX = 500.0f;

		cout << "Se ha creado un jugador.\n\n";
	}
	Player::~Player()
	{
		cout << "El jugador ha sido eliminado de la memoria.\n";
	}

	void Player::update(float deltaTime)
	{
		animIdleRight->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
		animIdleRight->update(deltaTime);
		gravityForce(deltaTime);
		keyPressed(deltaTime);
	}
	void Player::draw(RenderWindow* window)
	{
		window->draw(animIdleRight->target); // Ver igualaci�n de los sprites (renderer, animations, etc).
	}
	void Player::keyPressed(float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayLeft)))
		{
			renderer.move(-speedX * deltaTime, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayRight)))
		{
			renderer.move(speedX * deltaTime, 0.0f);
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
		return renderer.getPosition().y > floor->getRenderer().getPosition().y - floor->getRenderer().getGlobalBounds().height / 2.0f;
	}
	void Player::collisionWith(Floor* floor)
	{
		gravity.onTheFloor = true;
		renderer.setPosition(renderer.getPosition().x, floor->getRenderer().getPosition().y - floor->getRenderer().getGlobalBounds().height / 2.0f);
	}

	void Player::gravityForce(float deltaTime)
	{
		gravity.actualSpeed += gravity.acceleration * deltaTime;

		if (!gravity.onTheFloor)
		{
			renderer.move(0.0f, gravity.actualSpeed * deltaTime);
		}
	}
	void Player::initAnimations(float x, float y)
	{
		int left = 0; // Variable para agregar los frames a trav�s del ancho del total de la imagen.

		#pragma region PARADO HACIA LA DERECHA

		if (!textureLoader.loadFromFile("res/sprites/player/idle_right.png"))
		{
			cout << "La textura idle_right.png no se ha cargado.\n";
		}
		spriteLoader.setTexture(textureLoader);
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
	}
}
