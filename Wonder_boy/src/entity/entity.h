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

		Vector2f getInitialPosition();
		void setInitialPosition(float x, float y);

	private:
		Vector2f initialPosition;
	};
}

#endif // !ENTITY_H
