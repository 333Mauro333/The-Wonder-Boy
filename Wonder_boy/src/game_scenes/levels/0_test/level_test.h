#ifndef LEVEL_TEST_H
#define LEVEL_TEST_H

#include "game_scenes/scene.h"
#include "player/player.h"
#include "floor/floor.h"


namespace the_wonder_boy
{
	class LevelTest : public Scene
	{
	public:
		LevelTest(RenderWindow* window);
		~LevelTest();

		void init() override;
		void update(float deltaTime) override;
		void draw() override;

	private:
		Player* player;
		static const int floorSize = 15;
		Floor* floor[floorSize];

		void destroy() override;
	};
}

#endif // !LEVEL_TEST_H
