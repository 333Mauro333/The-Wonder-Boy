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


enum class ANIMATION_STATE { IDLE_RIGHT, IDLE_LEFT };

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
		Sprite getRenderer();

	private:
		View myView;
		ANIMATION_STATE animationState; // Enumerador de animaciones para asignar valores.
		Texture texIdleRight;
		Texture texIdleLeft; // HACER LO DE LA C�MARA PARA QUE SIGA AL JUGADOR. TAMBI�N; AGREGAR CAJAS DE COLISIONES.
		Sprite spriteLoader; // Variable para cargar sprites.

		Sprite renderer; // Sprite "central", el que todas las animaciones van a tener como base.
		GRAVITY gravity; // Estructura con valores de gravedad.
		float speedX; // Velocidad horizontal.

		Animation* animIdleRight; // Animaci�n parado mirando hacia la derecha.
		Animation* animIdleLeft; // Animaci�n parado mirando hacia la izquierda.

		void gravityForce(float deltaTime);
		void initAnimations(float x, float y);
		void updateAnimations(float deltaTime);
	};
}

#endif // !PLAYER_H
