#ifndef HUD_H
#define HUD_H

#include "SFML/Graphics.hpp"

#include "player/player.h"

using sf::RenderWindow;
using sf::RectangleShape;


namespace the_wonder_boy
{
	class HUD
	{
	public:
		HUD(RenderWindow* window, Player* player);
		~HUD();

		void update();
		void draw(RenderWindow* window);

	private:
		RenderWindow* window;
		Player* player;
		RectangleShape backHud;
		Sprite sprLife;
		Texture tex;

		static const int amountOfRectangles = 32;
		RectangleShape healthBars[amountOfRectangles];

		Vector2f posZero;
	};
}

#endif // !HUD_H
