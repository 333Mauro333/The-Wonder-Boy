#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>

#include "SFML/Graphics.hpp"

#include "entity/entity.h"
#include "text_string/text_string.h"

using std::string;
using sf::RectangleShape;
using sf::Texture;
using sf::Sprite;
using sf::RenderWindow;


namespace the_wonder_boy
{
	class Button : public Entity
	{
	public:
		Button(float x, float y, float w, float h, string optionName);
		~Button();

		void update();
		void draw(RenderWindow* window);

		void setSelected(bool selected);

	private:
		Texture _texButton;
		Sprite _sprButton;
		TextString* _text;

		bool _selected;

		void loadButtonSprite(float x, float y, float w, float h);
		void loadText(float x, float y, float w, float h, string optionName);
	};
}

#endif // !BUTTON_H
