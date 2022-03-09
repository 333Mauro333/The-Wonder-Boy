#ifndef SIGN_H
#define SIGN_H

#include "SFML/Graphics.hpp"

using sf::Vector2f;
using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;


enum class SIGN_TYPE { FIRST, SECOND, THIRD, FOURTH, GOAL };

namespace the_wonder_boy
{
	class Sign
	{
	public:
		Sign(float x, float y, SIGN_TYPE signType);
		~Sign();

		void draw(RenderWindow* window);

		SIGN_TYPE getSignType();
		Sprite getRenderer();
		void setPosition(Vector2f position);

	private:
		Vector2f _position;

		Texture _texSign;
		Sprite _sprSign;

		SIGN_TYPE _signType;

		void initSprite(float x, float y);
	};
}

#endif // !SIGN_H
