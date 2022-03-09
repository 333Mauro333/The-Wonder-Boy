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

		_pointsValue = 10;

		cout << "Se ha creado un caracol.\n\n";
	}
	Snail::~Snail()
	{
		cout << "El caracol ha sido eliminado de la memoria.\n";
	}


	// Funciones públicas.
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
		if (_active && !_defeated)
		{
			_defeated = true;
			setNewAnimation(ANIMATION_STATE_ENEMY::DEFEATED);
			_gravity.actualSpeed = -_bounceForce;
			accommodateAnimations();
		}
	}


	// Funciones privadas.
	void Snail::initSprites()
	{
		if (!_texEnemy.loadFromFile("res/sprites/enemies/snail.png"))
		{
			cout << "La textura de snail.png no se ha cargado.\n";
		}
		_sprLoader.setTexture(_texEnemy);
	}
	void Snail::initAnimations(float x, float y)
	{
		int left = 0; // Variable para agregar los frames a través del ancho del total de la imagen.
		int frameWidth = 0;
		int frameHeight = 0;
		float frameDuration = 0.0f;
		int amountOfFrames = 0;


		#pragma region NORMAL

		frameWidth = 78;
		frameHeight = 71;
		frameDuration = 0.5f;
		amountOfFrames = 3;

		_sprLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		_sprLoader.setPosition(x, y);
		_boxCollision.setSize(Vector2f(frameWidth, frameHeight));
		_boxCollision.setOrigin(frameWidth / 2.0f, frameHeight);
		_animNormal = new Animation(_sprLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animNormal->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region VENCIDO

		left += frameWidth * 2;
		frameWidth = 78;
		frameHeight = 71;
		frameDuration = 1.0f;
		amountOfFrames = 1;

		_sprLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight));
		_sprLoader.setPosition(x, y);
		_boxCollision.setSize(Vector2f(frameWidth, frameHeight));
		_boxCollision.setOrigin(frameWidth / 2.0f, frameHeight);
		_animDefeated = new Animation(_sprLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animDefeated->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion
	}
	void Snail::updateAnimations(float deltaTime)
	{
		if (_active)
		{
			updateAnimationEvents();

			switch (_animationState)
			{
			case ANIMATION_STATE_ENEMY::NORMAL:
				_animNormal->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
				_animNormal->update(deltaTime);
				break;

			case ANIMATION_STATE_ENEMY::DEFEATED:
				_animDefeated->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
				_animDefeated->update(deltaTime);
				break;
			}
		}
	}
	void Snail::drawAnimations(RenderWindow* window)
	{
		if (_active)
		{
			switch (_animationState)
			{
			case ANIMATION_STATE_ENEMY::NORMAL:
				window->draw(_animNormal->_target);
				break;

			case ANIMATION_STATE_ENEMY::DEFEATED:
				window->draw(_animDefeated->_target);
				break;
			}
		}
	}
	void Snail::accommodateAnimations()
	{
		_boxCollision.setPosition(_renderer.getPosition());
		updateAnimations(0.0f);
	}
	void Snail::updateAnimationEvents()
	{
		if (_animNormal->getNumberOfFrame() == 2)
		{
			_animNormal->resetAnimation();
			_renderer.setPosition(_renderer.getPosition().x - _boxCollision.getGlobalBounds().width / 15.0f, _renderer.getPosition().y);
			accommodateAnimations();
		}
	}
}
