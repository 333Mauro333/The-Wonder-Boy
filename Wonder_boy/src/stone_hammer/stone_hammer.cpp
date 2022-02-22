#include "stone_hammer.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	StoneHammer::StoneHammer()
	{
		animationState = ANIMATION_STATE::THROWN_RIGHT;
		isThrown = false;

		initAnimations();

		boxCollision.setFillColor(sf::Color(255, 0, 0, 128));
		boxCollision.setSize(Vector2f(63.0f, 63.0f));
		boxCollision.setOrigin(31.0f, 31.0f);

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
		updateAnimations(deltaTime);
	}
	void StoneHammer::draw(RenderWindow* window)
	{
		drawAnimations(window);
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
		frameDuration = 0.1f;
		amountOfFrames = 4;

		if (!texThrownRight.loadFromFile("res/sprites/player/stone_hammer_right.png"))
		{
			cout << "La textura stone_hammer_right.png no se ha cargado.\n";
		}
		sprLoader.setTexture(texThrownRight);
		sprLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
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
		sprLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
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
		case ANIMATION_STATE::THROWN_RIGHT:
			animThrownRight->update(deltaTime);
			break;

		case ANIMATION_STATE::THROWN_LEFT:
			animThrownLeft->update(deltaTime);
			break;
		}
	}
	void StoneHammer::drawAnimations(RenderWindow* window)
	{
		if (!isThrown)
		{
			switch (animationState)
			{
			case ANIMATION_STATE::THROWN_RIGHT:
				window->draw(animThrownRight->target);
				break;

			case ANIMATION_STATE::THROWN_LEFT:
				window->draw(animThrownLeft->target);
				break;
			}
		}
	}
}
