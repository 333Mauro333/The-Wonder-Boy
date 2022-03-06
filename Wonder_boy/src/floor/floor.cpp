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
		if (!texFloor.loadFromFile("res/sprites/scenes/level_test/floor.png"))
		{
			cout << "La textura del piso no se ha cargado.\n";
		}
			break;

		case FLOOR_TYPE::START:
			if (!texFloor.loadFromFile("res/sprites/scenes/level_test/floor_start.png"))
			{
				cout << "La textura del piso inicial no se ha cargado.\n";
			}
			break;

		case FLOOR_TYPE::END:
			if (!texFloor.loadFromFile("res/sprites/scenes/level_test/floor_end.png"))
			{
				cout << "La textura del piso final no se ha cargado.\n";
			}
			break;
		}

		sprFloor.setTexture(texFloor);
		sprFloor.setOrigin(sprFloor.getGlobalBounds().width / 2.0f, 0.0f);
		sprFloor.setPosition(x, y);

		boxCollision.setSize(Vector2f(sprFloor.getGlobalBounds().width, sprFloor.getGlobalBounds().height / 10.0f));
		boxCollision.setOrigin(boxCollision.getGlobalBounds().width / 2.0f, 0.0f);
		boxCollision.setPosition(x, y);
		boxCollision.setFillColor(sf::Color(255, 0, 0, 128));

		cout << "Se ha creado un piso.\n\n";
	}
	Floor::~Floor()
	{
		cout << "El piso ha sido eliminado de la memoria.\n";
	}

	// Funciones públicas.
	void Floor::draw(RenderWindow* window)
	{
		window->draw(sprFloor);

		#if _DEBUG

		window->draw(boxCollision);

		#endif // _DEBUG
	}

	RectangleShape Floor::getBoxCollision()
	{
		return boxCollision;
	}

	void Floor::setPosition(float x, float y)
	{
		sprFloor.setPosition(x, y);
		boxCollision.setPosition(x, y);
	}
}
