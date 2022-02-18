#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>

#include "SFML/Graphics.hpp"

#include "entity/entity.h"

using std::string;
using sf::RectangleShape;
using sf::Texture;
using sf::Sprite;
using sf::RenderWindow;
using sf::Font;
using sf::Text;


namespace the_wonder_boy
{
	class Button : public Entity
	{
	public:
		Button(float x, float y, float w, float h, string optionName);
		~Button();

		void draw(RenderWindow* window);

	private:
		RectangleShape back;
		Texture texButton;
		Sprite sprButton;
		Font font;
		Text text;
	};
}

#endif // !BUTTON_H
