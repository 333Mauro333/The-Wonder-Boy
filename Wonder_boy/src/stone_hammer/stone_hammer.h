#ifndef STONE_HAMMER_H
#define STONE_HAMMER_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"
#include "animation/animation.h"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::RectangleShape;


enum class ANIMATION_STATE { THROWN_RIGHT, THROWN_LEFT };

namespace the_wonder_boy
{
	class StoneHammer
	{
	public:
		StoneHammer();
		~StoneHammer();

		void update(float deltaTime);
		void draw(RenderWindow* window);

		bool getIsThrown();
		Vector2f getPosition();
		void setPosition(float x, float y);

	private:
		Texture texThrownRight; // Textura del martillo lanzado hacia la derecha.
		Texture texThrownLeft; // Textura del martillo lanzado hacia la izquierda.

		Sprite sprLoader; // Variable para cargar los sprites en las animaciones.
		Sprite renderer; // Sprite "central", al cual van a seguir todas las animaciones.

		ANIMATION_STATE animationState;
		Animation* animThrownRight;
		Animation* animThrownLeft;

		RectangleShape boxCollision;

		bool isThrown;

		void initAnimations();
		void updateAnimations(float deltaTime);
		void drawAnimations(RenderWindow* window);
	};
}

#endif // !STONE_HAMMER_H
