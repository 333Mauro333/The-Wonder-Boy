#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"

using sf::RectangleShape;
using sf::Texture;
using sf::Sprite;
using sf::RenderWindow;


namespace the_wonder_boy
{
	class Button : public Entity
	{
	public:
		Button(float x, float y, float w, float h);
		~Button();

	private:
		RectangleShape back;
		Texture tex;
		Sprite spr;

		void draw(RenderWindow* window);
	};
}

#endif // !BUTTON_H
