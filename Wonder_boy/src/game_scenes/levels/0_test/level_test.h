#ifndef LEVEL_TEST_H
#define LEVEL_TEST_H

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


namespace the_wonder_boy
{
	class LevelTest : public Scene
	{
	public:
		LevelTest(RenderWindow* window);
		~LevelTest();

		void update() override;
		void draw() override;
		void checkKeyPressedOnce(Keyboard::Key key) override;
		void checkKeyReleased(Keyboard::Key key) override;

	private:
		bool reseted;
		bool end;
		bool changeScene = false;

		Font font;
		Text winMessage;

		RectangleShape background;
		View view;
		Player* player;
		HUD* hud;


		static const int floorSize = 40;
		Floor* floor[floorSize];

		static const int platformSize = 2;
		Platform* platform[platformSize];

		static const int signSize = 5;
		Sign* sign[signSize];

		static const int fruitSize = 10;
		Fruit* fruit[fruitSize];

		static const int stoneSize = 3;
		Stone* stone[stoneSize];

		static const int bonfireSize = 2;
		Bonfire* bonfire[bonfireSize];

		static const int enemySize = 20;
		Enemy* enemy[enemySize];

		void init() override;
		void destroy() override;

		// Start: Posición de la escena donde la cámara va a empezar a moverse.
		// End: Posición de la escena donde la cámara va a terminar de moverse.
		// Distance: La cantidad total que va a moverse sobre "y" desde el comienzo hasta el final.
		// Una cantidad negativa movería la cámara hacia arriba.
		void moveCameraInY(float start, float end, float pixelsToMove);
		void updateCamera();

		Vector2f getPlayerCheckpointPosition();

		void resetLevel();

		void checkIfPlayerWon();
	};
}

#endif // !LEVEL_TEST_H
