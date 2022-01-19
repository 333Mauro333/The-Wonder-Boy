#ifndef ENTITY_H
#define ENTITY_H

#include "SFML/Window.hpp"

using sf::Vector2f;


namespace the_wonder_boy
{
	class Entity
	{
	public:
		Entity(float x, float y);
		~Entity();

		Vector2f getPosition();

	private:
		Vector2f position;
	};
}

#endif // !ENTITY_H
