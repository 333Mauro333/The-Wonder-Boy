#include "floor.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Floor::Floor(float x, float y) : Entity(x, y)
	{
		if (!texFloor.loadFromFile("res/sprites/scenes/level_test/floor.png"))
		{
			cout << "La textura del piso no se ha cargado.\n";
		}
		sprFloor.setTexture(texFloor);
		sprFloor.setOrigin(sprFloor.getGlobalBounds().width / 2.0f, sprFloor.getGlobalBounds().height / 2.0f);
		sprFloor.setPosition(x, y);

		boxCollision = RectangleShape(Vector2f(sprFloor.getGlobalBounds().width, sprFloor.getGlobalBounds().height));
		boxCollision.setOrigin(boxCollision.getGlobalBounds().width / 2.0f, boxCollision.getGlobalBounds().height / 2.0f);
		boxCollision.setPosition(x, y + boxCollision.getGlobalBounds().height / 2.0f);
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
}