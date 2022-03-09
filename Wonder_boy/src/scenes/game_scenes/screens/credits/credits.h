#ifndef CREDITS_H
#define CREDITS_H

#include "scenes/scene/scene.h"

#include "SFML/Graphics.hpp"

using sf::Vector2f;
using sf::RectangleShape;
using sf::Font;
using sf::Text;


namespace the_wonder_boy
{
	class Credits : public Scene
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
		Font _font;
		Text _textProgrammer;

		void init() override;
		void destroy() override;
	};
}

#endif // !CREDITS_H
