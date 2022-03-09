#ifndef GAME_CONTROLS_H
#define GAME_CONTROLS_H

#include "SFML/Window.hpp"

using sf::Keyboard;


enum class WANTED_KEY {SCREEN_UP, SCREEN_DOWN, SCREEN_ENTER, SCREEN_RETURN,
						GAMEPLAY_LEFT, GAMEPLAY_RIGHT, GAMEPLAY_JUMP, GAMEPLAY_ATTACK, GAMEPLAY_PAUSE };

namespace the_wonder_boy
{
	class ControlsManager
	{
	public:
		static Keyboard::Key getKey(WANTED_KEY wantedKey);

	private:
		const static int _screenUp;
		const static int _screenDown;
		const static int _screenEnter;
		const static int _screenReturn;

		const static int _gameplayLeft;
		const static int _gameplayRight;
		const static int _gameplayJump;
		const static int _gameplayAttack;
		const static int _gameplayPause;
	};
}

#endif // !GAME_CONTROLS_H
