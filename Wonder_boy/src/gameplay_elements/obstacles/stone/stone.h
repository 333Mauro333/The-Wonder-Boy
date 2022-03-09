#ifndef STONE_H
#define STONE_H

#include "SFML/Graphics.hpp"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::RectangleShape;
using sf::Vector2f;


namespace the_wonder_boy
{
	class Stone
	{
	public:
		Stone(float x, float y);
		~Stone();

		void draw(RenderWindow* window);

		RectangleShape getBoxCollision();
		float getDamage();

	private:
		Texture _texStone;
		Sprite _sprStone;
		RectangleShape _boxCollision;

		float _damage;

		void initSprite(float x, float y);
	};
}

#endif // !STONE_H
