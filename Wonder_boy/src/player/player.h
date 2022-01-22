#ifndef PLAYER_H
#define PLAYER_H

#include "entity/entity.h"
#include "floor/floor.h"

#include "SFML/Graphics.hpp"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;


namespace the_wonder_boy
{
	class Player : public Entity
	{
	public:
		Player(float x, float y);
		~Player();

		void update(float deltaTime);
		void draw(RenderWindow* window);
		void keyPressed(float deltaTime);
		bool isCollidingWith(Floor* floor);
		void collisionWith(Floor* floor);

	private:
		Texture tex_idle;
		Sprite spr_idle;

		GRAVITY gravity;

		float speedX;

		void gravityForce(float deltaTime);
	};
}

#endif // !PLAYER_H
