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
		FRUIT_TYPE fruitType;

		Texture texFruit;
		Sprite sprFruit;

		RectangleShape boxCollision;

		static float timeToDeactivate;

		bool active;
		bool taken;
		float healthValue;
		int pointsValue;
		float counterToDeactivate;

		void updateCountdown(float deltaTime);
	};
}

#endif // !FRUITS_H
