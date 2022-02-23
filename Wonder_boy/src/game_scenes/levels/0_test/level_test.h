#ifndef LEVEL_TEST_H
#define LEVEL_TEST_H

#include "game_scenes/scene.h"

#include "hud/hud.h"
#include "player/player.h"
#include "floor/floor.h"
#include "obstacles/stone/stone.h"

using sf::View;


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
		RectangleShape background;
		View view;
		Player* player;
		HUD* hud;

		static const int floorSize = 50;
		Floor* floor[floorSize];

		static const int stoneSize = 3;
		Stone* stone[stoneSize];

		void init() override;
		void destroy() override;

		// Start: Posici�n de la escena donde la c�mara va a empezar a moverse.
		// End: Posici�n de la escena donde la c�mara va a terminar de moverse.
		// Distance: La cantidad total que va a moverse sobre "y" desde el comienzo hasta el final. Una cantidad negativa mover�a la
		// c�mara hacia arriba.
		void moveCameraInY(float start, float end, float pixelsToMove);
		void updateCamera();
	};
}

#endif // !LEVEL_TEST_H
