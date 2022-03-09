#include "controls_manager.h"


namespace the_wonder_boy
{
	const int ControlsManager::_screenUp = Keyboard::Up;
	const int ControlsManager::_screenDown = Keyboard::Down;
	const int ControlsManager::_screenEnter = Keyboard::Enter;
	const int ControlsManager::_screenReturn = Keyboard::BackSpace;

	const int ControlsManager::_gameplayLeft = Keyboard::Left;
	const int ControlsManager::_gameplayRight = Keyboard::Right;
	const int ControlsManager::_gameplayJump = Keyboard::LAlt;
	const int ControlsManager::_gameplayAttack = Keyboard::LControl;
	const int ControlsManager::_gameplayPause = Keyboard::P;


	// Funciones públicas.
	Keyboard::Key ControlsManager::getKey(WANTED_KEY wantedKey)
	{
		int keyToReturn = 0;

		switch (wantedKey)
		{
		case WANTED_KEY::SCREEN_UP:
			keyToReturn = _screenUp;
			break;

		case WANTED_KEY::SCREEN_DOWN:
			keyToReturn = _screenDown;
			break;

		case WANTED_KEY::SCREEN_ENTER:
			keyToReturn = _screenEnter;
			break;

		case WANTED_KEY::SCREEN_RETURN:
			keyToReturn = _screenReturn;
			break;

		case WANTED_KEY::GAMEPLAY_LEFT:
			keyToReturn = _gameplayLeft;
			break;

		case WANTED_KEY::GAMEPLAY_RIGHT:
			keyToReturn = _gameplayRight;
			break;

		case WANTED_KEY::GAMEPLAY_JUMP:
			keyToReturn = _gameplayJump;
			break;

		case WANTED_KEY::GAMEPLAY_ATTACK:
			keyToReturn = _gameplayAttack;
			break;

		case WANTED_KEY::GAMEPLAY_PAUSE:
			keyToReturn = _gameplayPause;
			break;

		default:
			return Keyboard::Key::Unknown;
			break;
		}

		return static_cast<Keyboard::Key>(keyToReturn);
	}
}
