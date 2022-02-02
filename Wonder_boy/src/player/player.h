#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"
#include "floor/floor.h"
#include "animation/animation.h"

using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;


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

	private:
		ANIMATION_STATE animationState; // Enumerador de animación actual para controlar el renderer.
		Texture textureLoader;
		Sprite spriteLoader;
		Sprite renderer; // Sprite "central", el que todas las animaciones van a tener como base.
		Animation* animIdleRight; // Comienzo de animaciones.
		GRAVITY gravity; // Estructura con valores de gravedad.
		float speedX; // Velocidad horizontal.

		void gravityForce(float deltaTime);
		void initAnimations(float x, float y);
	};
}

#endif // !PLAYER_H
