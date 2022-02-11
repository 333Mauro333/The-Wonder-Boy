#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"
#include "floor/floor.h"
#include "animation/animation.h"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::View;
using sf::RectangleShape;


enum class ANIMATION_STATE { IDLE_RIGHT, IDLE_LEFT };
enum class BOX_COLLISION_TYPE { ENTIRE, FEET };

namespace the_wonder_boy
{
	class Player : public Entity
	{
	public:
		Player(float x, float y);
		~Player();

		void update(float deltaTime);
		void draw(RenderWindow* window);
		void keyPressed(float deltaTime);
		bool isCollidingWith(Floor* floor);
		void collisionWith(Floor* floor);
		Vector2f getPosition();
		RectangleShape getBoxCollision(BOX_COLLISION_TYPE boxCollisionType);
		void setPosition(Vector2f position);


	private:
		ANIMATION_STATE animationState; // Enumerador de animaciones para asignar valores.
		Texture texIdleRight;
		Texture texIdleLeft;
		Sprite spriteLoader; // Variable para cargar sprites.

		RectangleShape boxEntire; // Caja de colisi�n (todo el personaje).

		Sprite renderer; // Sprite "central", el que todas las animaciones van a tener como base.
		GRAVITY gravity; // Estructura con valores de gravedad.
		float speedX; // Velocidad horizontal.

		Animation* animIdleRight; // Animaci�n parado mirando hacia la derecha.
		Animation* animIdleLeft; // Animaci�n parado mirando hacia la izquierda.

		void gravityForce(float deltaTime);
		void initAnimations(float x, float y);
		void updateAnimations(float deltaTime);
		void accommodateAnimations();
	};
}

#endif // !PLAYER_H
