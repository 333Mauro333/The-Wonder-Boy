#ifndef GAMEPLAY_1_H
#define GAMEPLAY_1_H

#include "SFML/Audio.hpp"

#include "scenes/level/level.h"

#include "text_string/text_string.h"
#include "gameplay_elements/background_elements/sign/sign.h"
#include "gameplay_elements/hud/hud.h"
#include "gameplay_elements/floor/floor.h"
#include "gameplay_elements/platform/platform.h"
#include "gameplay_elements/items/fruit/fruit.h"
#include "gameplay_elements/obstacles/stone/stone.h"
#include "gameplay_elements/obstacles/bonfire/bonfire.h"
#include "gameplay_elements/enemies/enemy/enemy.h"

using sf::View;
using sf::Music;


namespace the_wonder_boy
{
	class Level1 : public Level
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

		TextString* _winMessage;

		RectangleShape _background;
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

		void initBackground();
		void initText();
		void initFloors();
		void initPlatforms();
		void initSigns();
		void initFruits();
		void initStones();
		void initBonfires();
		void initEnemies();
		void initPlayer();

		void updateCamera() override;

		Vector2f getPlayerCheckpointPosition();
		void resetLevel();
		void checkIfPlayerWon();
	};
}

#endif // !GAMEPLAY_1_H
