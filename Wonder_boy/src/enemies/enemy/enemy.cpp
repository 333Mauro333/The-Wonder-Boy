#include "enemy.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Enemy::Enemy(float x, float y)
	{
		renderer.setPosition(x, y);

		gravity.actualSpeed = 0.0f;
		gravity.acceleration = 3750.0f;
		gravity.speedLimit = 1000.0f;
		gravity.onTheFloor = true;

		defeated = false;
		active = false;

		bounceForce = 1000.0f; // Realizando funciones y todo para la acción de perder.

		boxCollision.setFillColor(sf::Color(255, 0, 0, 128));

		animationState = ANIMATION_STATE_ENEMY::NORMAL;

		cout << "Se ha creado un enemigo.\n";
	}
	Enemy::~Enemy()
	{
		delete animNormal;
		delete animDefeated;

		cout << "El enemigo ha sido eliminado de la memoria.\n\n";
	}

	// Funciones públicas.
	RectangleShape Enemy::getBoxCollision()
	{
		return boxCollision;
	}
	Vector2f Enemy::getPosition()
	{
		return renderer.getPosition();
	}
	bool Enemy::isActive()
	{
		return active;
	}
	bool Enemy::isDefeated()
	{
		return defeated;
	}
	void Enemy::activate()
	{
		active = true;
	}
	void Enemy::deactivate()
	{
		active = false;
	}


	// Funciones privadas.
	void Enemy::gravityForce(float deltaTime)
	{
		if (active && defeated)
		{
			gravity.actualSpeed += gravity.acceleration * deltaTime;

			renderer.move(0.0f, gravity.actualSpeed * deltaTime);
		}
	}

	void Enemy::setNewAnimation(ANIMATION_STATE_ENEMY animation)
	{
		animationState = animation;
	}
}
