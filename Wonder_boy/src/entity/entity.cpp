#include "entity.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Entity::Entity(float x, float y)
	{
		initialPosition = { x, y };

		cout << "Se ha creado una entidad.\n";
	}
	Entity::~Entity()
	{
		cout << "La entidad ha sido eliminada de la memoria.\n\n";
	}

	Vector2f Entity::getInitialPosition()
	{
		return initialPosition;
	}
	void Entity::setInitialPosition(float x, float y)
	{
		initialPosition = { x, y };
	}
}
