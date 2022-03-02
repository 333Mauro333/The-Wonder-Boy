#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"

#include "animation/animation.h"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::RectangleShape;


enum class ANIMATION_STATE_ENEMY { NORMAL, DEFEATED };
enum class ENEMY_TYPE { SNAIL };

namespace the_wonder_boy
{
	class Enemy
	{
	public:
		Enemy(float x, float y);
		virtual ~Enemy();

		virtual void update(float deltaTime) = 0;
		virtual void draw(RenderWindow* window) = 0;

		virtual ENEMY_TYPE getEnemyType() = 0;
		RectangleShape getBoxCollision();
		bool isDefeated();

	protected:
		Texture texEnemy;

		Sprite sprLoader;
		Sprite renderer;

		RectangleShape boxCollision;

		ANIMATION_STATE_ENEMY animationState;
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
