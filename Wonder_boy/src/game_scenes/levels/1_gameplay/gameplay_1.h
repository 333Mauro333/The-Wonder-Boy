#ifndef GAMEPLAY_1_H
#define GAMEPLAY_1_H

#include "SFML/Audio.hpp"

#include "game_scenes/scene.h"

#include "background_elements/sign/sign.h"
#include "hud/hud.h"
#include "player/player.h"
#include "floor/floor.h"
#include "platform/platform.h"
#include "items/fruit/fruit.h"
#include "obstacles/stone/stone.h"
#include "obstacles/bonfire/bonfire.h"
#include "enemies/enemy/enemy.h"

using sf::View;
using sf::Font;
using sf::Text;
using sf::Music;


namespace the_wonder_boy
{
	class Gameplay1 : public Scene
	{
	public:
		Gameplay1(RenderWindow* window);
		~Gameplay1();

		void update() override;
		void draw() override;
		void checkKeyPressedOnce(Keyboard::Key key) override;
		void checkKeyReleased(Keyboard::Key key) override;

	private:
		bool reseted;
		bool end;
		bool changeScene;

		Font font;
		Text winMessage;

		RectangleShape background;
		View view;
		Player* player;
		HUD* hud;
		Texture texHammer;
		Sprite sprHammer;

		static const int floorSize = 70;
		Floor* floor[floorSize];

		static const int platformSize = 10;
		Platform* platform[platformSize];

		static const int signSize = 5;
		Sign* sign[signSize];

		static const int fruitSize = 30;
		Fruit* fruit[fruitSize];

		static const int stoneSize = 6;
		Stone* stone[stoneSize];

		static const int bonfireSize = 5;
		Bonfire* bonfire[bonfireSize];

		static const int enemySize = 35;
		Enemy* enemy[enemySize];

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
