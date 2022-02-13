#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"
#include "animation/animation.h"
#include "floor/floor.h"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::View;
using sf::RectangleShape;


enum class ANIMATION_STATE { IDLE_RIGHT, IDLE_LEFT };
enum class BOX_COLLISION_TYPE { ENTIRE, FEET };
enum class DIRECTION { LEFT, RIGHT };

struct WALKING_ACCELERATION
{
	float actualSpeed;
	float speedLimit;
	float acceleration;
};

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

		RectangleShape boxEntire; // Caja de colisión (todo el personaje).
		RectangleShape boxFeet; // Caja de colisión (pies).

		Sprite renderer; // Sprite "central", el que todas las animaciones van a tener como base.
		GRAVITY gravity; // Estructura con valores de gravedad.
		WALKING_ACCELERATION walkingSpeed;
		float speedX; // Limpiar el cpp de player. Borrar esta variable. Hacer una variable sola de multiplier.

		Animation* animIdleRight; // Animación parado mirando hacia la derecha.
		Animation* animIdleLeft; // Animación parado mirando hacia la izquierda.

		void gravityForce(float deltaTime);
		void walkingAccelerationForce(float deltaTime);
		void initAnimations(float x, float y);
		void updateAnimations(float deltaTime);
		void accommodateAnimations();
		void move(DIRECTION direction, float deltaTime);
		void jump(bool high);
	};
}

#endif // !PLAYER_H
