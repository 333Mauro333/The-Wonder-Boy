#include "stone_hammer.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	GRAVITY StoneHammer::baseGravity = { 50.0f, 750.0f, 500.0f, false };

	StoneHammer::StoneHammer() : Entity(0.0f, 0.0f)
	{
		animationState = ANIMATION_STATE_HAMMER::THROWN_RIGHT;
		isThrown = false;

		xSpeed = 1200.0f;

		initAnimations();

		boxCollision.setFillColor(sf::Color(255, 0, 0, 128));
		boxCollision.setSize(Vector2f(63.0f, 63.0f));
		boxCollision.setOrigin(boxCollision.getGlobalBounds().width / 2.0f, boxCollision.getGlobalBounds().height / 2.0f);

		gravity = baseGravity;

		cout << "Se ha creado un martillo de piedra.\n\n";
	}
	StoneHammer::~StoneHammer()
	{
		delete animThrownRight;
		delete animThrownLeft;

		cout << "El martillo de piedra ha sido eliminado de la memoria.\n\n";
	}


	// Funciones públicas.
	void StoneHammer::update(float deltaTime)
	{
		cout << "Posicion del renderer: (" << renderer.getPosition().x << ";" << renderer.getPosition().y << ")\n";

		if (isThrown)
		{
			gravityForce(deltaTime);
			if (animationState == ANIMATION_STATE_HAMMER::THROWN_RIGHT)
			{
				renderer.move(xSpeed * deltaTime, 0.0f);
			}
			else if (animationState == ANIMATION_STATE_HAMMER::THROWN_LEFT)
			{
				renderer.move(-xSpeed * deltaTime, 0.0f);
			}
			updateAnimations(deltaTime);
			accommodateAnimations();
		}

		cout << "Valor de la gravedad actual: " << gravity.actualSpeed << ".\n";
	}
	void StoneHammer::draw(RenderWindow* window)
	{
		drawAnimations(window);

		#if _DEBUG

		window->draw(boxCollision);

		#endif // _DEBUG
	}

	RectangleShape StoneHammer::getBoxCollision()
	{
		return boxCollision;
	}
	bool StoneHammer::getIsThrown()
	{
		return isThrown;
	}
	Vector2f StoneHammer::getPosition()
	{
		return renderer.getPosition();
	}
	void StoneHammer::setPosition(float x, float y)
	{
		renderer.setPosition(x, y);
	}

	void StoneHammer::throwIt(THROW_DIRECTION throwDirection)
	{
		if (!isThrown)
		{
			isThrown = true;

			switch (throwDirection)
			{
			case THROW_DIRECTION::LEFT:
				animationState = ANIMATION_STATE_HAMMER::THROWN_LEFT;
				break;

			case THROW_DIRECTION::RIGHT:
				animationState = ANIMATION_STATE_HAMMER::THROWN_RIGHT;
				break;
			}

			accommodateAnimations();
		}
	}

	void StoneHammer::hit()
	{
		isThrown = false;
		resetValues();
	}


	// Funciones privadas.
	void StoneHammer::initAnimations()
	{
		int left = 0; // Variable para agregar los frames a través del ancho del total de la imagen.
		int frameWidth = 0;
		int frameHeight = 0;
		float frameDuration = 0.0f;
		int amountOfFrames = 0;


		#pragma region LANZADO HACIA LA DERECHA

		frameWidth = 63;
		frameHeight = 63;
		frameDuration = 0.05f;
		amountOfFrames = 4;

		if (!texThrownRight.loadFromFile("res/sprites/player/stone_hammer_right.png"))
		{
			cout << "La textura stone_hammer_right.png no se ha cargado.\n";
		}
		sprLoader.setTexture(texThrownRight);
		sprLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight / 2));
		animThrownRight = new Animation(sprLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			animThrownRight->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region LANZADO HACIA LA DERECHA

		if (!texThrownLeft.loadFromFile("res/sprites/player/stone_hammer_left.png"))
		{
			cout << "La textura stone_hammer_left.png no se ha cargado.\n";
		}
		sprLoader.setTexture(texThrownLeft);
		sprLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight / 2));
		animThrownLeft = new Animation(sprLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			animThrownLeft->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion
	}
	void StoneHammer::updateAnimations(float deltaTime)
	{
		switch (animationState)
		{
		case ANIMATION_STATE_HAMMER::THROWN_RIGHT:
			animThrownRight->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
			animThrownRight->update(deltaTime);
			break;

		case ANIMATION_STATE_HAMMER::THROWN_LEFT:
			animThrownLeft->target.setPosition(renderer.getPosition().x, renderer.getPosition().y);
			animThrownLeft->update(deltaTime);
			break;
		}
	}
	void StoneHammer::drawAnimations(RenderWindow* window)
	{
		if (isThrown)
		{
			switch (animationState)
			{
			case ANIMATION_STATE_HAMMER::THROWN_RIGHT:
				window->draw(animThrownRight->target);
				break;

			case ANIMATION_STATE_HAMMER::THROWN_LEFT:
				window->draw(animThrownLeft->target);
				break;
			}
		}
	}
	void StoneHammer::accommodateAnimations()
	{
		boxCollision.setPosition(renderer.getPosition());
		updateAnimations(0.0f);
	}
	
	void StoneHammer::gravityForce(float deltaTime)
	{
		gravity.actualSpeed = (gravity.actualSpeed + gravity.acceleration * deltaTime > gravity.speedLimit) ? gravity.speedLimit : gravity.actualSpeed + gravity.acceleration * deltaTime;

		renderer.move(0.0f, gravity.actualSpeed * deltaTime);
	}

	void StoneHammer::resetValues()
	{
		gravity = baseGravity;
	}
}
