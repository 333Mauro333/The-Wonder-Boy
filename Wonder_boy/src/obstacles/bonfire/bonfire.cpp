#include "bonfire.h"

#include <iostream>

using std::cout;



namespace the_wonder_boy
{
	Bonfire::Bonfire(float x, float y)
	{
		initSprites();
		initAnimations(x, y);

		cout << "Se ha creado una fogata.\n\n";
	}
	Bonfire::~Bonfire()
	{
		delete animBonfire;

		cout << "La fogata ha sido eliminada de la memoria.\n\n";
	}


	// Funciones públicas.
	void Bonfire::update(float deltaTime)
	{
		animBonfire->update(deltaTime);
	}
	void Bonfire::draw(RenderWindow* window)
	{
		window->draw(animBonfire->target);
	}

	RectangleShape Bonfire::getBoxCollision()
	{
		return boxCollision;
	}


	// Funciones privadas.
	void Bonfire::initSprites()
	{
		if (!texBonfire.loadFromFile("res/sprites/obstacles/bonfire.png"))
		{
			cout << "La textura de bonfire.png no se ha cargado.\n";
		}
		sprBonfire.setTexture(texBonfire);
	}
	void Bonfire::initAnimations(float x, float y)
	{
		int left = 0; // Variable para agregar los frames a través del ancho del total de la imagen.
		int frameWidth = 0;
		int frameHeight = 0;
		float frameDuration = 0.0f;
		int amountOfFrames = 0;


		#pragma region PARADO HACIA LA DERECHA

		frameWidth = 87;
		frameHeight = 125;
		frameDuration = 0.1f;
		amountOfFrames = 3;


		sprBonfire.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		sprBonfire.setPosition(x, y);
		animBonfire = new Animation(sprBonfire, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			animBonfire->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion
	}
}