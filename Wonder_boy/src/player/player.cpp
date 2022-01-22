#include "player.h"

#include <iostream>

#include "game_manager/game_manager.h"
#include "game_controls/game_controls.h"

using std::cout;


namespace the_wonder_boy
{
	Player::Player(float x, float y) : Entity(x, y)
	{
		if (!tex_idle.loadFromFile("res/sprites/player/idle.png"))
		{
			cout << "La textura idle.png no se ha cargado.\n";
		}

		spr_idle.setTexture(tex_idle);
		spr_idle.setOrigin(spr_idle.getGlobalBounds().width / 2.0f, spr_idle.getGlobalBounds().height);
		spr_idle.setPosition(x, y);

		gravity.actualSpeed = 0.0f;
		gravity.acceleration = 1000.0f;
		gravity.speedLimit = 1000.0f;

		speedX = 250.0f;

		cout << "Se ha creado un jugador.\n\n";
	}
	Player::~Player()
	{
		cout << "El jugador ha sido eliminado de la memoria.\n";
	}

	void Player::update(float deltaTime)
	{
		gravityForce(deltaTime);
		keyPressed(deltaTime);
	}
	void Player::draw(RenderWindow* window)
	{
		window->draw(spr_idle);
	}
	void Player::keyPressed(float deltaTime)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayLeft)))
		{
			spr_idle.move(-speedX * deltaTime, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::gameplayRight)))
		{
			spr_idle.move(speedX * deltaTime, 0.0f);
		}
	}


	void Player::gravityForce(float deltaTime)
	{
		gravity.actualSpeed += gravity.acceleration * deltaTime;

		spr_idle.move(0.0f, gravity.actualSpeed * deltaTime);
	}

}
