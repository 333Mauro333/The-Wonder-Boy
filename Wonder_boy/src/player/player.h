#ifndef PLAYER_H
#define PLAYER_H

#include "entity/entity.h"

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

	private:
		Texture tex_idle;
		Sprite spr_idle;
	};
}

#endif // !PLAYER_H
