#ifndef FLOOR_H
#define FLOOR_H

#include "entity/entity.h"
#include "SFML/Graphics.hpp"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;


namespace the_wonder_boy
{
	class Floor : public Entity
	{
	public:
		Floor(float x, float y);
		~Floor();

		void draw(RenderWindow* window);

	private:
		Texture tex_floor;
		Sprite spr_floor;
	};
}

#endif // !FLOOR_H
