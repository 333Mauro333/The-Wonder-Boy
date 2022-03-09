#ifndef FLOOR_H
#define FLOOR_H

#include "entity/entity.h"
#include "SFML/Graphics.hpp"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::RectangleShape;


enum class FLOOR_TYPE { NORMAL, START, END };

namespace the_wonder_boy
{
	class Floor : public Entity
	{
	public:
		Floor(float x, float y, FLOOR_TYPE floorType);
		~Floor();

		void draw(RenderWindow* window);

		RectangleShape getBoxCollision();
		void setPosition(float x, float y);

	private:
		Texture _texFloor;
		Sprite _sprFloor;
		RectangleShape _boxCollision;
	};
}

#endif // !FLOOR_H
