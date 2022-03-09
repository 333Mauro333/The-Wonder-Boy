#include "floor.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Floor::Floor(float x, float y, FLOOR_TYPE floorType) : Entity(x, y)
	{
		switch (floorType)
		{
		case FLOOR_TYPE::NORMAL:
			if (!_texFloor.loadFromFile("res/sprites/scenes/level_test/floor.png"))
			{
				cout << "La textura del piso no se ha cargado.\n";
			}
			break;

		case FLOOR_TYPE::START:
			if (!_texFloor.loadFromFile("res/sprites/scenes/level_test/floor_start.png"))
			{
				cout << "La textura del piso inicial no se ha cargado.\n";
			}
			break;

		case FLOOR_TYPE::END:
			if (!_texFloor.loadFromFile("res/sprites/scenes/level_test/floor_end.png"))
			{
				cout << "La textura del piso final no se ha cargado.\n";
			}
			break;
		}

		_sprFloor.setTexture(_texFloor);
		_sprFloor.setOrigin(_sprFloor.getGlobalBounds().width / 2.0f, 0.0f);
		_sprFloor.setPosition(x, y);

		_boxCollision.setSize(Vector2f(_sprFloor.getGlobalBounds().width, _sprFloor.getGlobalBounds().height / 10.0f));
		_boxCollision.setOrigin(_boxCollision.getGlobalBounds().width / 2.0f, 0.0f);
		_boxCollision.setPosition(x, y);
		_boxCollision.setFillColor(sf::Color(255, 0, 0, 128));

		cout << "Se ha creado un piso.\n\n";
	}
	Floor::~Floor()
	{
		cout << "El piso ha sido eliminado de la memoria.\n";
	}

	// Funciones públicas.
	void Floor::draw(RenderWindow* window)
	{
		window->draw(_sprFloor);

		#if _DEBUG

		window->draw(_boxCollision);

		#endif // _DEBUG
	}

	RectangleShape Floor::getBoxCollision()
	{
		return _boxCollision;
	}
	void Floor::setPosition(float x, float y)
	{
		_sprFloor.setPosition(x, y);
		_boxCollision.setPosition(x, y);
	}
}
