#include "enemies/wasp/wasp.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Wasp::Wasp(float x, float y, WASP_VERTICAL_SPEED verticalSpeed) : Enemy(x, y)
	{
		cout << "Se ha creado una avispa.\n\n";

		this->verticalSpeed = verticalSpeed;

		gravity.speedLimit = 1200.0f;

		speedX = 100.0f;
		switch (verticalSpeed)
		{
		case WASP_VERTICAL_SPEED::SLOW:
			speedY = 500.0f;
			gravity.acceleration = 2000.0f;
			break;

		case WASP_VERTICAL_SPEED::NORMAL:
			speedY = 850.0f;
			gravity.acceleration = 3000.0f;
			break;

		case WASP_VERTICAL_SPEED::FAST:
			speedY = 1100.0f;
			break;
		}
		moveUp = true;

		gravity.actualSpeed = speedY / 2.0f;

		initSprites();
		initAnimations(x, y);

		pointsValue = 20;
	}
	Wasp::~Wasp()
	{
		cout << "La avispa ha sido eliminada de la memoria.\n";
	}


	// Funciones públicas.
	void Wasp::update(float deltaTime)
	{
		moveForward(deltaTime);
		moveUpAndDown(deltaTime, speedY);
		updateAnimations(deltaTime);
		accommodateAnimations();
	}
	void Wasp::draw(RenderWindow* window)
	{
		drawAnimations(window);

		#if _DEBUG

		window->draw(boxCollision);

		#endif // _DEBUG
	}

	ENEMY_TYPE Wasp::getEnemyType()
	{
		return ENEMY_TYPE::WASP;
	}

	void Wasp::defeat()
	{
		if (active && !defeated)
		{
			defeated = true;
			gravity.acceleration = 4000.0f;
			setNewAnimation(ANIMATION_STATE_ENEMY::DEFEATED);
			gravity.actualSpeed = -bounceForce;
			accommodateAnimations();
		}
	}

	void Wasp::reset()
	{
		switch (verticalSpeed)
		{
		case WASP_VERTICAL_SPEED::SLOW:
			speedY = 500.0f;
			gravity.acceleration = 2000.0f;
			break;

		case WASP_VERTICAL_SPEED::NORMAL:
			speedY = 850.0f;
			gravity.acceleration = 3000.0f;
			break;

		case WASP_VERTICAL_SPEED::FAST:
			speedY = 1100.0f;
			break;
		}

		gravity.actualSpeed = speedY / 2.0f;
		gravity.acceleration = 3750.0f;
		gravity.speedLimit = 1200.0f;
		gravity.onTheFloor = true;

		defeated = false;
		active = false;
		moveUp = true;

		renderer.setPosition(initialPosition);

		setNewAnimation(ANIMATION_STATE_ENEMY::NORMAL);
	}

	// Funciones privadas.
	void Wasp::initSprites()
	{
		if (!texEnemy.loadFromFile("res/sprites/enemies/wasp.png"))
		{
			cout << "La textura de wasp.png no se ha cargado.\n";
		}
		sprLoader.setTexture(texEnemy);
	}
	void Wasp::initAnimations(float x, float y)
	{
		int left = 0; // Variable para agregar los frames a través del ancho del total de la imagen.
		int frameWidth = 0;
		int frameHeight = 0;
		float frameDuration = 0.0f;
		int amountOfFrames = 0;


		#pragma region NORMAL

		frameWidth = 67;
		frameHeight = 100;
		frameDuration = 0.1f;
		amountOfFrames = 3;

		sprLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		sprLoader.setPosition(x, y);
		boxCollision.setSize(Vector2f(frameWidth, frameHeight));
		boxCollision.setOrigin(frameWidth / 2.0f, frameHeight);
		animNormal = new Animation(sprLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			animNormal->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region VENCIDO

		left += frameWidth * 2;
		frameWidth = 83;
		frameHeight = 100;
		frameDuration = 1.0f;
		amountOfFrames = 1;

		sprLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		sprLoader.setPosition(x, y);
		boxCollision.setSize(Vector2f(frameWidth, frameHeight));
		boxCollision.setOrigin(frameWidth / 2.0f, frameHeight);
		animDefeated = new Animation(sprLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			animDefeated->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion
	}
	void Wasp::updateAnimations(float deltaTime)
	{
		if (active)
		{
			updateAnimationEvents();

			switch (animationState)
			{
			case ANIMATION_STATE_ENEMY::NORMAL:
				animNormal->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
				animNormal->update(deltaTime);
				break;

			case ANIMATION_STATE_ENEMY::DEFEATED:
				animDefeated->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
				animDefeated->update(deltaTime);
				break;
			}
		}
	}
	void Wasp::drawAnimations(RenderWindow* window)
	{
		if (active)
		{
			switch (animationState)
			{
			case ANIMATION_STATE_ENEMY::NORMAL:
				window->draw(animNormal->target);
				break;

			case ANIMATION_STATE_ENEMY::DEFEATED:
				window->draw(animDefeated->target);
				break;
			}
		}
	}
	void Wasp::accommodateAnimations()
	{
		boxCollision.setPosition(renderer.getPosition());
		updateAnimations(0.0f);
	}
	void Wasp::updateAnimationEvents()
	{
		if (animNormal->getNumberOfFrame() == 2)
		{
			animNormal->resetAnimation();
			accommodateAnimations();
		}
	}

	void Wasp::moveForward(float deltaTime)
	{
		if (active && !defeated)
		{
			renderer.move(-speedX * deltaTime, 0.0f);
		}
	}
	void Wasp::moveUpAndDown(float deltaTime, float maxSpeed)
	{
		if (active)
		{
			if (!defeated)
			{
				if (gravity.actualSpeed + gravity.acceleration * deltaTime > maxSpeed)
				{
					moveUp = true;
				}
				else if (gravity.actualSpeed - gravity.acceleration * deltaTime < -maxSpeed)
				{
					moveUp = false;
				}

				if (moveUp)
				{
					gravity.actualSpeed -= gravity.acceleration * deltaTime;
				}
				else
				{
					gravity.actualSpeed += gravity.acceleration * deltaTime;
				}
			}
			else
			{
				gravity.actualSpeed = (gravity.actualSpeed + gravity.acceleration * deltaTime > gravity.speedLimit) ? gravity.speedLimit : gravity.actualSpeed + gravity.acceleration * deltaTime;
			}

			renderer.move(0.0f, gravity.actualSpeed * deltaTime);
		}
	}
}
