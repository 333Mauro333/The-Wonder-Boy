#ifndef HUD_H
#define HUD_H

#include <vector>

#include "SFML/Graphics.hpp"

#include "player/player.h"

using std::vector;
using std::string;
using sf::RenderWindow;
using sf::RectangleShape;
using sf::Font;
using sf::Text;


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
		Texture texLife;
		Sprite sprLife;
		Texture tex;
		Font font;
		Text textPoints;
		Text textLives;

		static const int amountOfRectangles = 32;
		RectangleShape healthBars[amountOfRectangles];

		Vector2f posZero;

		string toString(int num);
	};
}

#endif // !HUD_H
