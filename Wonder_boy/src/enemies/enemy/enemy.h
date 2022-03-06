#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"
#include "animation/animation.h"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::RectangleShape;


enum class ANIMATION_STATE_ENEMY { NORMAL, DEFEATED };
enum class ENEMY_TYPE { SNAIL, WASP };

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
		Vector2f getPosition();
		bool isActive();
		bool isDefeated();
		void activate();
		void deactivate();

		virtual void reset();
		
		virtual void defeat() = 0;

	protected:
		Texture texEnemy;

		Sprite sprLoader;
		Sprite renderer;

		Vector2f initialPosition;

		RectangleShape boxCollision;

		ANIMATION_STATE_ENEMY animationState;
		Animation* animNormal;
		Animation* animDefeated;

		GRAVITY gravity;

		bool active;
		bool defeated;

		float bounceForce;

		virtual void initSprites() = 0;
		virtual void initAnimations(float x, float y) = 0;
		virtual void updateAnimations(float deltaTime) = 0;
		virtual void drawAnimations(RenderWindow* window) = 0;

		void gravityForce(float deltaTime);

		void setNewAnimation(ANIMATION_STATE_ENEMY animation);
	};
}

#endif // !ENEMY_H
