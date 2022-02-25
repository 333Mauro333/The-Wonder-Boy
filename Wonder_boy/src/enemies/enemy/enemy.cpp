#include "enemy.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Enemy::Enemy(float x, float y)
	{
		renderer.setPosition(x, y);

		defeated = false;

		boxCollision.setFillColor(sf::Color(255, 0, 0, 128));

		cout << "Se ha creado un enemigo.\n";
	}
	Enemy::~Enemy()
	{
		delete animNormal;
		delete animDefeated;

		cout << "El enemigo ha sido eliminado de la memoria.\n\n";
	}

	RectangleShape Enemy::getBoxCollision()
	{
		return boxCollision;
	}
}
