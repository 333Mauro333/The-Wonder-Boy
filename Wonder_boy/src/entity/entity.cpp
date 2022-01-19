#include "entity.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Entity::Entity(float x, float y)
	{
		position = { x, y };

		cout << "Se ha creado una entidad.\n";
	}
	Entity::~Entity()
	{
		cout << "La entidad ha sido eliminada de la memoria.\n\n";
	}

	Vector2f Entity::getPosition()
	{
		return position;
	}
}