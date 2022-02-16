#ifndef LEVEL_TEST_H
#define LEVEL_TEST_H

#include "game_scenes/scene.h"

#include "player/player.h"
#include "floor/floor.h"

using sf::View;


namespace the_wonder_boy
{
	class LevelTest : public Scene
	{
	public:
		LevelTest(RenderWindow* window);
		~LevelTest();

		void update(float deltaTime) override;
		void draw() override;
		void checkKeyPressedOnce(Keyboard::Key key) override;
		void checkKeyReleased(Keyboard::Key key) override;

	private:
		View view;
		Player* player;
		static const int floorSize = 25;
		Floor* floor[floorSize];

		void init() override;
		void destroy() override;
		void updateCamera();
	};
}

#endif // !LEVEL_TEST_H
