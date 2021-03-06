#ifndef SNAIL_H
#define SNAIL_H

#include "gameplay_elements/enemies/enemy/enemy.h"


namespace the_wonder_boy
{
	class Snail : public Enemy
	{
	public:
		Snail(float x, float y);
		~Snail();

		void update(float deltaTime) override;
		void draw(RenderWindow* window) override;

		ENEMY_TYPE getEnemyType() override;

		void defeat() override;

	private:

		void initSprites() override;
		void initAnimations(float x, float y) override;
		void updateAnimations(float deltaTime) override;
		void drawAnimations(RenderWindow* window) override;
		void accommodateAnimations();
		void updateAnimationEvents();
	};
}

#endif // !SNAIL_H
