#include "entity.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Entity::Entity(float x, float y)
	{
		_initialPosition = { x, y };

		cout << "Se ha creado una entidad.\n";
	}
	Entity::~Entity()
	{
		cout << "La entidad ha sido eliminada de la memoria.\n\n";
	}

	// Funciones públicas.
	Vector2f Entity::getInitialPosition()
	{
		return _initialPosition;
	}
	void Entity::setInitialPosition(float x, float y)
	{
		_initialPosition = { x, y };
	}
}
