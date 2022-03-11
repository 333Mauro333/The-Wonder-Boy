#ifndef TEXT_STRING_H
#define TEXT_STRING_H

#include <iostream>

#include "SFML/Graphics.hpp"

using std::string;
using sf::RenderWindow;
using sf::Font;
using sf::Text;
using sf::Vector2f;
using sf::Color;

enum class FONT_TYPE { EIGHT_BIT, RETRO };
enum class ORIGIN { CORNER_UP_LEFT, UP_CENTER, CORNER_UP_RIGHT,
					LEFT_CENTER, CENTER, RIGHT_CENTER,
					CORNER_DOWN_LEFT, DOWN_CENTER, CORNER_DOWN_RIGHT };

namespace the_wonder_boy
{
	class TextString
	{
	public:
		TextString(FONT_TYPE fontType, string text, Vector2f position, Vector2f size, ORIGIN origin = ORIGIN::CORNER_UP_LEFT, Color color = Color::Black);
		~TextString();

		static void initFonts();
		void draw(RenderWindow* window);

		Text getText();
		bool getIsVisible();
		void setPosition(Vector2f position);
		void setIsVisible(bool isVisible);

	private:
		static Font _font8Bit;
		static Font _fontRetro;
		Text _text;

		bool _isVisible;

		void setFont(FONT_TYPE fontType);
		void setString(string text);
		void setOrigin(ORIGIN origin);
		void setSize(Vector2f size);
		void setColor(Color color);
	};
}

#endif // !TEXT_STRING_H
