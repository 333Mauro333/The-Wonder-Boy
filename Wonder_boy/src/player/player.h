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
		bool isCollidingWith(Floor* floor); // Responde a si el jugador est� pisando el piso.
		void collisionWith(Floor* floor); // Reacciona ante una colisi�n con el piso.
		Vector2f getPosition();
		RectangleShape getBoxCollision(BOX_COLLISION_TYPE boxCollisionType); // Obtiene la caja de colisi�n que se decida.
		void setPosition(Vector2f position);
		void keyPressedOnce(Keyboard::Key key);

	private:
		Texture texIdleRight;
		Texture texIdleLeft;

		RectangleShape boxEntire; // Caja de colisi�n (todo el personaje).
		RectangleShape boxFeet; // Caja de colisi�n (pies).

		Sprite spriteLoader; // Variable para cargar sprites.
		Sprite renderer; // Sprite "central", el que todas las animaciones van a tener como base.
		GRAVITY gravity; // Estructura con valores de gravedad.
		WALKING_ACCELERATION walkingSpeed; // Estructura con valores para la aceleraci�n al caminar.

		ANIMATION_STATE animationState; // Enumerador de animaciones para asignar valores.
		Animation* animIdleRight; // Animaci�n parado mirando hacia la derecha.
		Animation* animIdleLeft; // Animaci�n parado mirando hacia la izquierda.

		void initAnimations(float x, float y);
		void updateAnimations(float deltaTime);
		void drawAnimations(RenderWindow* window);
		void keyPressed(float deltaTime); // Realiza acciones seg�n qu� tecla est� presionada.
		void gravityForce(float deltaTime);
		void walkingAccelerationForce(float deltaTime);
		void accommodateAnimations();
		void move(DIRECTION direction, float deltaTime);
		void jump(bool high);
	};
}

#endif // !PLAYER_H
