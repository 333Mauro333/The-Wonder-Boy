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
		RectangleShape backHud;
		Player* player;

	};
}


#endif // !HUD_H

