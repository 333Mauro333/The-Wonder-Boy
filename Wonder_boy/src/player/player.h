#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"
#include "animation/animation.h"
#include "stone_hammer/stone_hammer.h"
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
		void keyPressedOnce(Keyboard::Key key); // Realiza acciones según qué tecla se phaya presionado en el frame actual.
		void keyReleased(Keyboard::Key key); // Realiza acciones según qué tecla se haya levantado.

		void collisionWith(Floor* floor); // Reacciona ante una colisión con el piso.
		
		Vector2f getPosition();
		RectangleShape getBoxCollision(BOX_COLLISION_TYPE boxCollisionType); // Obtiene la caja de colisión que se decida.
		Sprite getLifeSprite();
		Sprite getExtraLifeSprite();
		float getSpeed();
		float getHealth();
		float getFallingSpeed();
		void setPosition(Vector2f position);
		void setLost(bool lost);
		void stopWalkSpeed();
		void addHealth(float health);

	private:
		Texture texLife; // Textura del ícono para mostrar las vidas restantes.
		Texture texExtraLife; // Textura del ícono del ítem de la vida extra.
		Texture texIdleRight;
		Texture texIdleLeft;
		Texture texWalkingRight;
		Texture texWalkingLeft;
		Texture texJumpingRight;
		Texture texJumpingLeft;
		Texture texAttackingRight;
		Texture texAttackingLeft;

		Sprite sprLife; // Sprite del ícono para mostrar las vidas restantes.
		Sprite sprExtraLife; // Sprite del ícono del ítem de la vida extra.
		Sprite spriteLoader; // Variable para cargar sprites.
		Sprite renderer; // Sprite "central", el que todas las animaciones van a tener como base.
		WALKING_ACCELERATION walkingSpeed; // Estructura con valores para la aceleración al caminar.

		ANIMATION_STATE animationState; // Enumerador de animaciones para asignar valores.
		Animation* animIdleRight; // Animación parado mirando hacia la derecha.
		Animation* animIdleLeft; // Animación parado mirando hacia la izquierda.
		Animation* animWalkingRight; // Animación caminando hacia la derecha.
		Animation* animWalkingLeft; // Animación caminando hacia la izquierda.
		Animation* animJumpingRight; // Animación saltando hacia la derecha.
		Animation* animJumpingLeft; // Animación saltando hacia la izquierda.
		Animation* animAttackingRight; // Animación atacando hacia la derecha.
		Animation* animAttackingLeft; // Animación atacando hacia la izquierda.

		RectangleShape boxEntire; // Caja de colisión (todo el personaje).
		RectangleShape boxFeet; // Caja de colisión (pies).

		GRAVITY gravity; // Estructura con valores de gravedad.

		bool lost;
		float health;

		float forceJump = 1400.0f;
		float walkingAnimationSpeed = 0.075f;
		float speedLimit = 500.0f;

		static const int stoneHammersSize = 2;
		StoneHammer* stoneHammers[stoneHammersSize];
		int savedHammerPosition;

		void initSprites();
		void initAnimations(float x, float y);
		void updateAnimations(float deltaTime);
		void drawAnimations(RenderWindow* window);
		void accommodateAnimations();
		void setWalkingAnimationMode(SPEED speed);
		void updateAnimationEvents();
		bool actualAnimationIs(ANIMATION_STATE animationState);
		void setNewAnimation(ANIMATION_STATE animationState);

		void keyPressed(float deltaTime); // Realiza acciones según qué tecla esté presionada.
		void move(DIRECTION direction, float deltaTime);
		void jump(bool high);
		void attack(DIRECTION direction);
		void gravityForce(float deltaTime);
		void walkingAccelerationForce(float deltaTime);
		
		bool bothSidesPressed();
		bool noSidePressed();

		bool isThereASavedHammer();
		int saveAFreePosition();

		void updateStoneHammers(float deltaTime);
		void drawStoneHammers(RenderWindow* window);
	};
}

#endif // !PLAYER_H
