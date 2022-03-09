#include "stone.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Stone::Stone(float x, float y)
	{
		initSprite(x, y);

		_damage = 15.0f;

		cout << "Se ha creado una piedra.\n";
	}
	Stone::~Stone()
	{
		cout << "La piedra ha sido eliminada de la memoria.\n\n";
	}

	// Funciones públicas.
	void Stone::draw(RenderWindow* window)
	{
		window->draw(_sprStone);

		#if _DEBUG

		window->draw(_boxCollision);

		#endif // _DEBUG
	}

	RectangleShape Stone::getBoxCollision()
	{
		return _boxCollision;
	}
	float Stone::getDamage()
	{
		return _damage;
	}


	// Funciones privadas.
	void Stone::initSprite(float x, float y)
	{
		if (!_texStone.loadFromFile("res/sprites/obstacles/stone.png"))
		{
			cout << "La textura stone.png no se ha cargado.\n";
		}
		_sprStone.setTexture(_texStone);
		_sprStone.setOrigin(_sprStone.getGlobalBounds().width / 2.0f, _sprStone.getGlobalBounds().height);
		_sprStone.setPosition(x, y);

		_boxCollision.setFillColor(sf::Color(255, 0, 0, 128));
		_boxCollision.setSize(Vector2f(_sprStone.getGlobalBounds().width / 10.0f * 8.0f, _sprStone.getGlobalBounds().height / 10.0f * 8.0f));
		_boxCollision.setOrigin(_boxCollision.getGlobalBounds().width / 2.0f, _boxCollision.getGlobalBounds().height);
		_boxCollision.setPosition(x, y);
	}
}
