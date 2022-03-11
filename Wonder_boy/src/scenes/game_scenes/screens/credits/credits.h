#ifndef CREDITS_H
#define CREDITS_H

#include "SFML/Graphics.hpp"

#include "scenes/screen/screen.h"
#include "text_string/text_string.h"

using sf::Vector2f;
using sf::RectangleShape;


namespace the_wonder_boy
{
	class Credits : public Screen
	{
	public:
		Credits(RenderWindow* window);
		~Credits();

		void update() override;
		void draw() override;
		void checkKeyPressedOnce(Keyboard::Key key) override;
		void checkKeyReleased(Keyboard::Key key) override;

	private:
		RectangleShape _background;
		TextString* _textProgrammer;

		void init() override;
		void destroy() override;

		void initText();
	};
}

#endif // !CREDITS_H
