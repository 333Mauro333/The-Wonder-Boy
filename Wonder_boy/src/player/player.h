#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"
#include "animation/animation.h"
#include "stone_hammer/stone_hammer.h"
#include "floor/floor.h"
#include "obstacles/stone/stone.h"

using sf::RenderWindow;
using sf::View;
using sf::Keyboard;
using sf::RectangleShape;
using sf::Texture;
using sf::Sprite;


enum class ANIMATION_STATE { IDLE_RIGHT, IDLE_LEFT, WALKING_RIGHT, WALKING_LEFT,
							JUMPING_RIGHT, JUMPING_LEFT, ATTACKING_RIGHT, ATTACKING_LEFT,
							TRIPPING_RIGHT, TRIPPING_LEFT,
							LOSING_NORMAL };
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
		void keyPressedOnce(Keyboard::Key key); // Realiza acciones seg�n qu� tecla se phaya presionado en el frame actual.
		void keyReleased(Keyboard::Key key); // Realiza acciones seg�n qu� tecla se haya levantado.

		void collisionWith(Floor* floor); // Reacciona ante una colisi�n con el piso.
		
		Vector2f getPosition();
		RectangleShape getBoxCollision(BOX_COLLISION_TYPE boxCollisionType); // Obtiene la caja de colisi�n que se decida.
		Sprite getLifeSprite();
		Sprite getExtraLifeSprite();
		float getSpeed();
		bool getHit();
		float getHealth();
		float getFallingSpeed();
		StoneHammer* getPlayerStoneHammer(int position);
		static int getStoneHammersSize();
		DIRECTION getActualAnimationDirection();
		bool isAlive();
		void setPosition(Vector2f position);
		void stopWalkSpeed();
		void addHealth(float health);
		void receiveDamage(float damage);

		void tripOn(Stone* stone); // Tropezarse.
		void lose();

	private:
		#pragma region TEXTURAS

		Texture texLife; // Textura del �cono para mostrar las vidas restantes.
		Texture texExtraLife; // Textura del �cono del �tem de la vida extra.
		Texture texIdleRight;
		Texture texIdleLeft;
		Texture texWalkingRight;
		Texture texWalkingLeft;
		Texture texJumpingRight;
		Texture texJumpingLeft;
		Texture texAttackingRight;
		Texture texAttackingLeft;
		Texture texTrippingRight;
		Texture texTrippingLeft;
		Texture texLosingNormal;

		#pragma endregion

		#pragma region SPRITES

		Sprite sprLife; // Sprite del �cono para mostrar las vidas restantes.
		Sprite sprExtraLife; // Sprite del �cono del �tem de la vida extra.
		Sprite spriteLoader; // Variable para cargar sprites.
		Sprite renderer; // Sprite "central", el que todas las animaciones van a tener como base.

		#pragma endregion
		
		#pragma region ANIMACIONES

		Animation* animIdleRight; // Animaci�n parado mirando hacia la derecha.
		Animation* animIdleLeft; // Animaci�n parado mirando hacia la izquierda.
		Animation* animWalkingRight; // Animaci�n caminando hacia la derecha.
		Animation* animWalkingLeft; // Animaci�n caminando hacia la izquierda.
		Animation* animJumpingRight; // Animaci�n saltando hacia la derecha.
		Animation* animJumpingLeft; // Animaci�n saltando hacia la izquierda.
		Animation* animAttackingRight; // Animaci�n atacando hacia la derecha.
		Animation* animAttackingLeft; // Animaci�n atacando hacia la izquierda.
		Animation* animTrippingRight; // Animaci�n tropez�ndose hacia la derecha.
		Animation* animTrippingLeft; // Animaci�n tropez�ndose hacia la izquierda.
		Animation* animLosingNormal; // Animaci�n perdiendo normalmente.

		#pragma endregion

		ANIMATION_STATE animationState; // Enumerador de animaciones para asignar valores.

		GRAVITY gravity; // Estructura con valores de gravedad.
		WALKING_ACCELERATION walkingSpeed; // Estructura con valores para la aceleraci�n al caminar.

		RectangleShape boxEntire; // Caja de colisi�n (todo el personaje).
		RectangleShape boxFeet; // Caja de colisi�n (pies).

		float health;
		bool hit;
		bool bouncedWhenDied;

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

		void keyPressed(float deltaTime); // Realiza acciones seg�n qu� tecla est� presionada.
		void move(DIRECTION direction, float deltaTime);
		void jump(bool high);
		void attack(DIRECTION direction);
		void drainHealth(float deltaTime);
		void gravityForce(float deltaTime);
		void walkingAccelerationForce(float deltaTime);
		void bounceWhenDies();
		
		bool bothSidesPressed();
		bool noSidePressed();

		bool isThereASavedHammer();
		int saveAFreePosition();

		void updateStoneHammers(float deltaTime);
		void drawStoneHammers(RenderWindow* window);
	};
}

#endif // !PLAYER_H
