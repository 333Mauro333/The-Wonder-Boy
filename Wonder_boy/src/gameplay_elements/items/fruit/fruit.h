#ifndef FRUITS_H
#define FRUITS_H

#include "SFML/Graphics.hpp"

using sf::RenderWindow;
using sf::Vector2f;
using sf::Texture;
using sf::Sprite;
using sf::RectangleShape;


enum class FRUIT_TYPE { APPLE, BANANAS, CARROT, TOMATO };

namespace the_wonder_boy
{
	class Fruit
	{
	public:
		Fruit(float x, float y, FRUIT_TYPE fruitType);
		~Fruit();

		void update(float deltaTime);
		void draw(RenderWindow* window);

		RectangleShape getBoxCollision();
		Vector2f getPosition();
		float getHealthValue();
		int getPointsValue();
		bool isActive();
		bool wasTaken();

		void activate();
		void take();

		void reset();

	private:
		FRUIT_TYPE _fruitType;

		Texture _texFruit;
		Sprite _sprFruit;

		RectangleShape _boxCollision;

		static float _timeToDeactivate;

		bool _active;
		bool _taken;
		float _healthValue;
		int _pointsValue;
		float _counterToDeactivate;

		void updateCountdown(float deltaTime);
	};
}

#endif // !FRUITS_H
