#ifndef FLOOR_H
#define FLOOR_H

#include "entity/entity.h"
#include "SFML/Graphics.hpp"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::RectangleShape;


namespace the_wonder_boy
{
	class Floor : public Entity
	{
	public:
		Floor(float x, float y);
		~Floor();

		void draw(RenderWindow* window);

		RectangleShape getBoxCollision();

	private:
		Texture texFloor;
		Sprite sprFloor;
		RectangleShape boxCollision;
	};
}

#endif // !FLOOR_H
