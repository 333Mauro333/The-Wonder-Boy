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
		int getPoints();
		bool isActive();
		bool isDefeated();
		void setActive(bool active);

		virtual void reset();
		
		virtual void defeat() = 0;

	protected:
		Texture _texEnemy;

		Sprite _sprLoader;
		Sprite _renderer;

		Vector2f _initialPosition;

		RectangleShape _boxCollision;

		ANIMATION_STATE_ENEMY _animationState;
		Animation* _animNormal;
		Animation* _animDefeated;

		GRAVITY _gravity;

		bool _active;
		bool _defeated;
		int _pointsValue;

		float _bounceForce;

		virtual void initSprites() = 0;
		virtual void initAnimations(float x, float y) = 0;
		virtual void updateAnimations(float deltaTime) = 0;
		virtual void drawAnimations(RenderWindow* window) = 0;

		void gravityForce(float deltaTime);

		void setNewAnimation(ANIMATION_STATE_ENEMY animationState);
	};
}

#endif // !ENEMY_H
