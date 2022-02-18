#include "floor.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Floor::Floor(float x, float y) : Entity(x, y)
	{
		if (!tex_floor.loadFromFile("res/sprites/scenes/level_test/floor.png"))
		{
			cout << "La textura del piso no se ha cargado.\n";
		}
		spr_floor.setTexture(tex_floor);
		spr_floor.setOrigin(spr_floor.getGlobalBounds().width / 2.0f, spr_floor.getGlobalBounds().height / 2.0f);
		spr_floor.setPosition(x, y);

		cout << "Se ha creado un piso.\n\n";
	}
	Floor::~Floor()
	{
		cout << "El piso ha sido eliminado de la memoria.\n";
	}

	// Funciones públicas.
	void Floor::draw(RenderWindow* window)
	{
		window->draw(spr_floor);
	}

	Sprite Floor::getRenderer()
	{
		return spr_floor;
	}
}