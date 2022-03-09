#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"

#include "entity/entity.h"
#include "animation/animation.h"
#include "gameplay_elements/stone_hammer/stone_hammer.h"
#include "gameplay_elements/floor/floor.h"
#include "gameplay_elements/platform/platform.h"
#include "gameplay_elements/obstacles/stone/stone.h"

using sf::RenderWindow;
using sf::View;
using sf::Keyboard;
using sf::RectangleShape;
using sf::Texture;
using sf::Sprite;


enum class ANIMATION_STATE { IDLE_RIGHT, IDLE_LEFT, WALKING_RIGHT, WALKING_LEFT,
							JUMPING_RIGHT, JUMPING_LEFT, ATTACKING_RIGHT, ATTACKING_LEFT,
							TRIPPING_RIGHT, TRIPPING_LEFT,
							LOSING_NORMAL, LOSING_BURNED_1, LOSING_BURNED_2,
							WIN };
enum class BOX_COLLISION_TYPE { ENTIRE, FEET };
enum class DIRECTION { LEFT, RIGHT };
enum class SPEED { NORMAL, FAST };
enum class LOSING_TYPE { NORMAL, BURNED };

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
		void collisionWith(Platform* platform); // Reacciona ante una colisi�n con una plataforma.
		void collisionWith(Sprite hammerItem);
		
		Vector2f getPosition();
		RectangleShape getBoxCollision(BOX_COLLISION_TYPE boxCollisionType); // Obtiene la caja de colisi�n que se decida.
		float getSpeed();
		bool getHit();
		static unsigned int getLives();
		static unsigned int getPoints();
		float getHealth();
		float getFallingSpeed();
		StoneHammer* getPlayerStoneHammer(int position);
		static int getStoneHammersSize();
		DIRECTION getActualAnimationDirection();
		void setPosition(Vector2f position);
		void setNecessaryDistanceToWin(float distance);
		void stopWalkSpeed();
		static void setAmountOfLives(unsigned int newLives);
		static void setAmountOfPoints(unsigned int newPoints);

		bool isAlive();
		bool won();
		void addLife();
		void subtractLife();
		void addHealth(float health);
		void receiveDamage(float damage);
		void addPoints(int pointsToAdd);

		void tripOn(Stone* stone); // Tropezarse.
		void lose(LOSING_TYPE losingType);
		void winLevel();
		void reset();

	private:
		#pragma region TEXTURAS

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
		Texture texLosingBurned;
		Texture texWin;

		#pragma endregion

		#pragma region SPRITES

		Sprite spriteLoader; // Variable para cargar sprites.
		Sprite renderer; // Sprite "central", el que todas las animaciones van a tener como base para la posici�n.

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
		Animation* animLosingBurned1; // Animaci�n perdiendo quemado (parte 1).
		Animation* animLosingBurned2; // Animaci�n perdiendo quemado (parte 2).
		Animation* animWin; // Animaci�n festejando.

		#pragma endregion

		ANIMATION_STATE animationState; // Enumerador de animaciones para asignar valores.

		GRAVITY gravity; // Estructura con valores de gravedad.
		WALKING_ACCELERATION walkingSpeed; // Estructura con valores para la aceleraci�n al caminar.

		RectangleShape boxEntire; // Caja de colisi�n (todo el personaje).
		RectangleShape boxFeet; // Caja de colisi�n (pies).

		static unsigned int lives;
		static unsigned int points;

		float health;
		bool canAttack;
		bool threw;
		bool hit;
		bool bouncedWhenDied;
		bool wins;
		float necessaryDistanceToWin;

		float forceJump = 1400.0f;
		float walkingAnimationSpeed = 0.075f;
		float speedLimit = 500.0f;

		static const int stoneHammersSize = 2;
		StoneHammer* stoneHammers[stoneHammersSize];
		int savedHammerPosition;

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
		void checkDistanceToWin();
		
		bool bothSidesPressed();
		bool noSidePressed();

		bool isThereASavedHammer();
		int saveAFreePosition();

		void updateStoneHammers(float deltaTime);
		void drawStoneHammers(RenderWindow* window);
	};
}

#endif // !PLAYER_H
