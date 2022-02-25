#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"

#include "animation/animation.h"

using sf::RenderWindow;
using sf::Sprite;
using sf::RectangleShape;


enum class ANIMATION_STATE_ENEMY { NORMAL, DEFEATED };

namespace the_wonder_boy
{
	class Enemy
	{
	public:
		Enemy(float x, float y);
		virtual ~Enemy();

		virtual void update(float deltaTime) = 0;
		virtual void draw(RenderWindow* window) = 0;

		RectangleShape getBoxCollision();

	protected:
		Sprite sprLoader;
		Sprite renderer;

		RectangleShape boxCollision;

		Animation* animNormal;
		Animation* animDefeated;

		bool defeated;

		virtual void initSprites() = 0;
		virtual void initAnimations(float x, float y) = 0;
		virtual void updateAnimations(float deltaTime) = 0;
		virtual void drawAnimations(RenderWindow* window) = 0;
	};
}

#endif // !ENEMY_H
