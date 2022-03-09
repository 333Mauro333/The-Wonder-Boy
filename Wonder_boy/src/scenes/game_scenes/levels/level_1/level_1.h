#ifndef GAMEPLAY_1_H
#define GAMEPLAY_1_H

#include "SFML/Audio.hpp"

#include "scenes/scene/scene.h"

#include "gameplay_elements/background_elements/sign/sign.h"
#include "gameplay_elements/hud/hud.h"
#include "gameplay_elements/player/player.h"
#include "gameplay_elements/floor/floor.h"
#include "gameplay_elements/platform/platform.h"
#include "gameplay_elements/items/fruit/fruit.h"
#include "gameplay_elements/obstacles/stone/stone.h"
#include "gameplay_elements/obstacles/bonfire/bonfire.h"
#include "gameplay_elements/enemies/enemy/enemy.h"

using sf::View;
using sf::Font;
using sf::Text;
using sf::Music;


namespace the_wonder_boy
{
	class Level1 : public Scene
	{
	public:
		Level1(RenderWindow* window);
		~Level1();

		void update() override;
		void draw() override;
		void checkKeyPressedOnce(Keyboard::Key key) override;
		void checkKeyReleased(Keyboard::Key key) override;

	private:
		bool _reseted;
		bool _end;
		bool _changeScene;

		Font _font;
		Text _winMessage;

		RectangleShape _background;
		View _view;
		Player* _player;
		HUD* _hud;
		Texture _texHammer;
		Sprite _sprHammer;

		Music _music;

		static const int _floorSize = 70;
		Floor* _floor[_floorSize];

		static const int _platformSize = 10;
		Platform* _platform[_platformSize];

		static const int _signSize = 5;
		Sign* _sign[_signSize];

		static const int _fruitSize = 30;
		Fruit* _fruit[_fruitSize];

		static const int _stoneSize = 6;
		Stone* _stone[_stoneSize];

		static const int _bonfireSize = 5;
		Bonfire* _bonfire[_bonfireSize];

		static const int _enemySize = 35;
		Enemy* _enemy[_enemySize];

		void init() override;
		void destroy() override;

		void moveCameraInY(float start, float end, float pixelsToMove);
		void updateCamera();

		Vector2f getPlayerCheckpointPosition();
		void resetLevel();
		void checkIfPlayerWon();
	};
}

#endif // !GAMEPLAY_1_H
