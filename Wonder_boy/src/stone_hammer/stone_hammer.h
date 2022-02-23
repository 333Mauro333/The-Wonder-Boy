#ifndef STONE_HAMMER_H
#define STONE_HAMMER_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"
#include "animation/animation.h"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::RectangleShape;


enum class ANIMATION_STATE_HAMMER { THROWN_RIGHT, THROWN_LEFT };
enum class THROW_DIRECTION { LEFT, RIGHT };

namespace the_wonder_boy
{
	class StoneHammer : public Entity
	{
	public:
		StoneHammer();
		~StoneHammer();

		void update(float deltaTime);
		void draw(RenderWindow* window);

		RectangleShape getBoxCollision();
		Vector2f getPosition();
		bool getIsThrown();
		void setPosition(float x, float y);

		void throwIt(THROW_DIRECTION throwDirection);

		void hit();

	private:
		Texture texThrownRight; // Textura del martillo lanzado hacia la derecha.
		Texture texThrownLeft; // Textura del martillo lanzado hacia la izquierda.

		Sprite sprLoader; // Variable para cargar los sprites en las animaciones.
		Sprite renderer; // Sprite "central", al cual van a seguir todas las animaciones.

		ANIMATION_STATE_HAMMER animationState;
		Animation* animThrownRight;
		Animation* animThrownLeft;

		RectangleShape boxCollision;

		static GRAVITY baseGravity;
		GRAVITY gravity;

		bool isThrown;

		float xSpeed;

		void initAnimations();
		void updateAnimations(float deltaTime);
		void drawAnimations(RenderWindow* window);
		void accommodateAnimations();

		void gravityForce(float deltaTime);

		void resetValues();
	};
}

#endif // !STONE_HAMMER_H
