#include "enemy.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Enemy::Enemy(float x, float y)
	{
		_initialPosition = { x, y };

		_renderer.setPosition(x, y);

		_gravity.actualSpeed = 0.0f;
		_gravity.acceleration = 3750.0f;
		_gravity.speedLimit = 1000.0f;
		_gravity.onTheFloor = true;

		_defeated = false;
		_active = false;
		_pointsValue = 0;

		_bounceForce = 1000.0f;

		_boxCollision.setFillColor(sf::Color(255, 0, 0, 128));

		setNewAnimation(ANIMATION_STATE_ENEMY::NORMAL);

		cout << "Se ha creado un enemigo.\n";
	}
	Enemy::~Enemy()
	{
		delete _animNormal;
		delete _animDefeated;

		cout << "El enemigo ha sido eliminado de la memoria.\n\n";
	}

	// Funciones públicas.
	RectangleShape Enemy::getBoxCollision()
	{
		return _boxCollision;
	}
	Vector2f Enemy::getPosition()
	{
		return _renderer.getPosition();
	}
	int Enemy::getPoints()
	{
		return _pointsValue;
	}
	bool Enemy::isActive()
	{
		return _active;
	}
	bool Enemy::isDefeated()
	{
		return _defeated;
	}
	void Enemy::setActive(bool active)
	{
		_active = active;
	}

	void Enemy::reset()
	{
		_gravity.actualSpeed = 0.0f;
		_gravity.acceleration = 3750.0f;
		_gravity.speedLimit = 1000.0f;
		_gravity.onTheFloor = true;

		_defeated = false;
		_active = false;

		_renderer.setPosition(_initialPosition);

		setNewAnimation(ANIMATION_STATE_ENEMY::NORMAL);
	}


	// Funciones privadas.
	void Enemy::gravityForce(float deltaTime)
	{
		if (_active && _defeated)
		{
			_gravity.actualSpeed += _gravity.acceleration * deltaTime;

			_renderer.move(0.0f, _gravity.actualSpeed * deltaTime);
		}
	}

	void Enemy::setNewAnimation(ANIMATION_STATE_ENEMY animationState)
	{
		_animationState = animationState;
	}
}
