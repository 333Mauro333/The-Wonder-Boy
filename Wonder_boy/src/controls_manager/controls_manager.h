#ifndef GAME_CONTROLS_H
#define GAME_CONTROLS_H

#include "SFML/Window.hpp"

using sf::Keyboard;


namespace the_wonder_boy
{
	class ControlsManager
	{
	public:
		static int screenUp;
		static int screenDown;
		static int screenEnter;
		static int screenReturn;

		static int gameplayLeft;
		static int gameplayRight;
		static int gameplayJump;
		static int gameplayAttack;
		static int gameplayPause;
	};
}

#endif // !GAME_CONTROLS_H
