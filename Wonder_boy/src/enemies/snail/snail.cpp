#include "snail.h"

#include <iostream>

using std::cout;
using sf::Vector2f;


namespace the_wonder_boy
{
	Snail::Snail(float x, float y) : Enemy(x, y)
	{
		initSprites();
		initAnimations(x, y);

		cout << "Se ha creado un caracol.\n\n";
	}
	Snail::~Snail()
	{
		cout << "El caracol ha sido eliminado de la memoria.\n";
	}


	// Funciones p�blicas.
	void Snail::update(float deltaTime)
	{
		updateAnimations(deltaTime);
		gravityForce(deltaTime);
		accommodateAnimations();
	}
	void Snail::draw(RenderWindow* window)
	{
		drawAnimations(window);

		#if _DEBUG

		window->draw(boxCollision);

		#endif // _DEBUG
	}

	ENEMY_TYPE Snail::getEnemyType()
	{
		return ENEMY_TYPE::SNAIL;
	}

	void Snail::defeat()
	{
		if (active && !defeated)
		{
			defeated = true;
			setNewAnimation(ANIMATION_STATE_ENEMY::DEFEATED);
			gravity.actualSpeed = -bounceForce;
			accommodateAnimations();
		}
	}


	// Funciones privadas.
	void Snail::initSprites()
	{
		if (!texEnemy.loadFromFile("res/sprites/enemies/snail.png"))
		{
			cout << "La textura de snail.png no se ha cargado.\n";
		}
		sprLoader.setTexture(texEnemy);
	}
	void Snail::initAnimations(float x, float y)
	{
		int left = 0; // Variable para agregar los frames a trav�s del ancho del total de la imagen.
		int frameWidth = 0;
		int frameHeight = 0;
		float frameDuration = 0.0f;
		int amountOfFrames = 0;


		#pragma region NORMAL

		frameWidth = 83;
		frameHeight = 87;
		frameDuration = 0.5f;
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
		frameHeight = 87;
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
	void Snail::updateAnimations(float deltaTime)
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
	void Snail::drawAnimations(RenderWindow* window)
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
	void Snail::accommodateAnimations()
	{
		boxCollision.setPosition(renderer.getPosition());
		updateAnimations(0.0f);
	}
	void Snail::updateAnimationEvents()
	{
		if (animNormal->getNumberOfFrame() == 2)
		{
			animNormal->resetAnimation();
			renderer.setPosition(renderer.getPosition().x - boxCollision.getGlobalBounds().width / 15.0f, renderer.getPosition().y);
			accommodateAnimations();
		}
	}
}
