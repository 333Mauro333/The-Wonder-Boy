#ifndef LEVEL_TEST_H
#define LEVEL_TEST_H

#include "game_scenes/scene.h"


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
		void destroy() override;

	private:

	};
}

#endif // !LEVEL_TEST_H
