#ifndef PLATFORM_H
#define PLATFORM_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"

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
		Texture _texPlatform;
		Sprite _sprPlatform;

		RectangleShape _boxCollision;
	};
}

#endif // !PLATFORM_H
