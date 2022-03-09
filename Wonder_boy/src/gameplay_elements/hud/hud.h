#ifndef HUD_H
#define HUD_H

#include <iostream>

#include "SFML/Graphics.hpp"

#include "gameplay_elements/player/player.h"

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
		RenderWindow* _window;
		Player* _player;
		RectangleShape _backHud;
		Texture _texLife;
		Sprite _sprLife;
		Texture _tex;
		Font _font;
		Text _textPoints;
		Text _textLives;

		static const int _amountOfRectangles = 32;
		RectangleShape _healthBars[_amountOfRectangles];

		Vector2f _posZero;

		string toString(int num);
	};
}

#endif // !HUD_H
