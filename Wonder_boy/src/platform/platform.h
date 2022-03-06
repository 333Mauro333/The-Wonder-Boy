#ifndef PLATFORM_H
#define PLATFORM_H

#include "entity/entity.h"

#include "SFML/Graphics.hpp"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::RectangleShape;


namespace the_wonder_boy
{
	class Platform : public Entity
	{
	public:
		Platform(float x, float y);
		~Platform();

		void draw(RenderWindow* window);

		RectangleShape getBoxCollision();

	private:
		Texture texPlatform;
		Sprite sprPlatform;

		RectangleShape boxCollision;
	};
}

#endif // !PLATFORM_H
