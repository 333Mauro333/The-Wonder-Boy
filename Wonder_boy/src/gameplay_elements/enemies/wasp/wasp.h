#ifndef WASP_H
#define WASP_H

#include "gameplay_elements/enemies/enemy/enemy.h"


enum class WASP_VERTICAL_SPEED { SLOW, NORMAL, FAST };

namespace the_wonder_boy
{
	class Wasp : public Enemy
	{
	public:
		Wasp(float x, float y, WASP_VERTICAL_SPEED verticalSpeed);
		~Wasp();

		void update(float deltaTime) override;
		void draw(RenderWindow* window) override;

		ENEMY_TYPE getEnemyType() override;

		void defeat() override;

		void reset() override;

	private:
		float speedX;
		float speedY;
		bool moveUp;

		WASP_VERTICAL_SPEED verticalSpeed;

		void initSprites() override;
		void initAnimations(float x, float y) override;
		void updateAnimations(float deltaTime) override;
		void drawAnimations(RenderWindow* window) override;
		void accommodateAnimations();
		void updateAnimationEvents();

		void moveForward(float deltaTime);
		void moveUpAndDown(float deltaTime, float maxSpeed);
	};
}

#endif // !WASP_H
