#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"
#include "animation/animation.h"
#include "floor/floor.h"

using sf::RenderWindow;
using sf::View;
using sf::Keyboard;
using sf::RectangleShape;
using sf::Texture;
using sf::Sprite;


enum class ANIMATION_STATE { IDLE_RIGHT, IDLE_LEFT, WALKING_RIGHT, WALKING_LEFT,
							JUMPING_RIGHT, JUMPING_LEFT, ATTACKING_RIGHT, ATTACKING_LEFT };
enum class BOX_COLLISION_TYPE { ENTIRE, FEET };
enum class DIRECTION { LEFT, RIGHT };
enum class SPEED { NORMAL, FAST };

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

		bool isCollidingWith(Floor* floor); // Responde a si el jugador est� pisando el piso.
		void collisionWith(Floor* floor); // Reacciona ante una colisi�n con el piso.
		
		Vector2f getPosition();
		RectangleShape getBoxCollision(BOX_COLLISION_TYPE boxCollisionType); // Obtiene la caja de colisi�n que se decida.
		void setPosition(Vector2f position);
		
		void keyPressedOnce(Keyboard::Key key); // Realiza acciones seg�n qu� tecla se phaya presionado en el frame actual.
		void keyReleased(Keyboard::Key key); // Realiza acciones seg�n qu� tecla se haya levantado.

	private:
		Texture texIdleRight;
		Texture texIdleLeft;
		Texture texWalkingRight;
		Texture texWalkingLeft;
		Texture texJumpingRight;
		Texture texJumpingLeft;
		Texture texAttackingRight;
		Texture texAttackingLeft;

		RectangleShape boxEntire; // Caja de colisi�n (todo el personaje).
		RectangleShape boxFeet; // Caja de colisi�n (pies).

		Sprite spriteLoader; // Variable para cargar sprites.
		Sprite renderer; // Sprite "central", el que todas las animaciones van a tener como base.
		GRAVITY gravity; // Estructura con valores de gravedad.
		WALKING_ACCELERATION walkingSpeed; // Estructura con valores para la aceleraci�n al caminar.

		ANIMATION_STATE animationState; // Enumerador de animaciones para asignar valores.
		Animation* animIdleRight; // Animaci�n parado mirando hacia la derecha.
		Animation* animIdleLeft; // Animaci�n parado mirando hacia la izquierda.
		Animation* animWalkingRight; // Animaci�n caminando hacia la derecha.
		Animation* animWalkingLeft; // Animaci�n caminando hacia la izquierda.
		Animation* animJumpingRight; // Animaci�n saltando hacia la derecha.
		Animation* animJumpingLeft; // Animaci�n saltando hacia la izquierda.
		Animation* animAttackingRight; // Animaci�n atacando hacia la derecha.
		Animation* animAttackingLeft; // Animaci�n atacando hacia la izquierda.

		float walkingAnimationSpeed = 0.075f;
		float forceJump = 1400.0f;
		float speedLimit = 500.0f;

		void initAnimations(float x, float y);
		void updateAnimations(float deltaTime);
		void drawAnimations(RenderWindow* window);
		void accommodateAnimations();
		void setWalkingAnimationMode(SPEED speed);
		void updateAnimationEvents();

		void keyPressed(float deltaTime); // Realiza acciones seg�n qu� tecla est� presionada.
		void move(DIRECTION direction, float deltaTime);
		void jump(bool high);
		void gravityForce(float deltaTime);
		void walkingAccelerationForce(float deltaTime);
		
		bool bothSidesPressed();
		bool noSidePressed();
		bool isAttacking(DIRECTION direction);
	};
}

#endif // !PLAYER_H
