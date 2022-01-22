#include "floor.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Floor::Floor(float x, float y) : Entity(x, y)
	{
		if (!tex_floor.loadFromFile("res/sprites/levels/level_test/floor.png"))
		{
			cout << "La textura idle.png no se ha cargado.\n";
		}

		spr_floor.setTexture(tex_floor);
		spr_floor.setOrigin(spr_floor.getGlobalBounds().width / 2.0f, spr_floor.getGlobalBounds().height);
		spr_floor.setPosition(x, y);
	}
	Floor::~Floor()
	{
		cout << "El piso ha sido eliminado de la memoria.\n";
	}

	void Floor::draw(RenderWindow* window)
	{
		window->draw(spr_floor);
	}
}