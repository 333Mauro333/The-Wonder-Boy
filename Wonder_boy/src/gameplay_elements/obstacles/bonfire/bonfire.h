#ifndef BONFIRE_H
#define BONFIRE_H

#include "SFML/Graphics.hpp"

#include "animation/animation.h"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::RectangleShape;


namespace the_wonder_boy
{
	class Bonfire
	{
	public:
		Bonfire(float x, float y);
		~Bonfire();

		void update(float deltaTime);
		void draw(RenderWindow* window);

		RectangleShape getBoxCollision();

	private:
		Texture _texBonfire;
		Sprite _sprBonfire;
		Animation* _animBonfire;
		RectangleShape _boxCollision;

		void initSprites();
		void initAnimations(float x, float y);
	};
}

#endif // !BONFIRE_H
