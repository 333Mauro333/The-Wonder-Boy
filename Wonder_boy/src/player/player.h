#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"
#include "animation/animation.h"
#include "floor/floor.h"

using sf::RenderWindow;
using sf::Keyboard;
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
		bool isCollidingWith(Floor* floor); // Responde a si el jugador está pisando el piso.
		void collisionWith(Floor* floor); // Reacciona ante una colisión con el piso.
		Vector2f getPosition();
		RectangleShape getBoxCollision(BOX_COLLISION_TYPE boxCollisionType); // Obtiene la caja de colisión que se decida.
		void setPosition(Vector2f position);
		void keyPressedOnce(Keyboard::Key key);

	private:
		Texture texIdleRight;
		Texture texIdleLeft;

		RectangleShape boxEntire; // Caja de colisión (todo el personaje).
		RectangleShape boxFeet; // Caja de colisión (pies).

		Sprite spriteLoader; // Variable para cargar sprites.
		Sprite renderer; // Sprite "central", el que todas las animaciones van a tener como base.
		GRAVITY gravity; // Estructura con valores de gravedad.
		WALKING_ACCELERATION walkingSpeed; // Estructura con valores para la aceleración al caminar.

		ANIMATION_STATE animationState; // Enumerador de animaciones para asignar valores.
		Animation* animIdleRight; // Animación parado mirando hacia la derecha.
		Animation* animIdleLeft; // Animación parado mirando hacia la izquierda.

		void initAnimations(float x, float y);
		void updateAnimations(float deltaTime);
		void drawAnimations(RenderWindow* window);
		void keyPressed(float deltaTime); // Realiza acciones según qué tecla esté presionada.
		void gravityForce(float deltaTime);
		void walkingAccelerationForce(float deltaTime);
		void accommodateAnimations();
		void move(DIRECTION direction, float deltaTime);
		void jump(bool high);
	};
}

#endif // !PLAYER_H
