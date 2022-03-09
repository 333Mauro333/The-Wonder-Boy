#include "wasp.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Wasp::Wasp(float x, float y, WASP_VERTICAL_SPEED verticalSpeed) : Enemy(x, y)
	{
		cout << "Se ha creado una avispa.\n\n";

		_verticalSpeed = verticalSpeed;

		_gravity.speedLimit = 1200.0f;

		_speedX = 100.0f;
		switch (verticalSpeed)
		{
		case WASP_VERTICAL_SPEED::SLOW:
			_maxSpeedY = 500.0f;
			_gravity.acceleration = 2000.0f;
			break;

		case WASP_VERTICAL_SPEED::NORMAL:
			_maxSpeedY = 850.0f;
			_gravity.acceleration = 3000.0f;
			break;

		case WASP_VERTICAL_SPEED::FAST:
			_maxSpeedY = 1100.0f;
			break;
		}
		_moveUp = true;

		_gravity.actualSpeed = _maxSpeedY / 2.0f;

		initSprites();
		initAnimations(x, y);

		_pointsValue = 20;
	}
	Wasp::~Wasp()
	{
		cout << "La avispa ha sido eliminada de la memoria.\n";
	}


	// Funciones públicas.
	void Wasp::update(float deltaTime)
	{
		moveForward(deltaTime);
		moveUpAndDown(deltaTime);
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
		if (_active && !_defeated)
		{
			_defeated = true;
			_gravity.acceleration = 4000.0f;
			setNewAnimation(ANIMATION_STATE_ENEMY::DEFEATED);
			_gravity.actualSpeed = -_bounceForce;
			accommodateAnimations();
		}
	}

	void Wasp::reset()
	{
		switch (_verticalSpeed)
		{
		case WASP_VERTICAL_SPEED::SLOW:
			_maxSpeedY = 500.0f;
			_gravity.acceleration = 2000.0f;
			break;

		case WASP_VERTICAL_SPEED::NORMAL:
			_maxSpeedY = 850.0f;
			_gravity.acceleration = 3000.0f;
			break;

		case WASP_VERTICAL_SPEED::FAST:
			_maxSpeedY = 1100.0f;
			break;
		}

		_gravity.actualSpeed = _maxSpeedY / 2.0f;
		_gravity.acceleration = 3750.0f;
		_gravity.speedLimit = 1200.0f;
		_gravity.onTheFloor = true;

		_defeated = false;
		_active = false;
		_moveUp = true;

		_renderer.setPosition(_initialPosition);

		setNewAnimation(ANIMATION_STATE_ENEMY::NORMAL);
	}

	// Funciones privadas.
	void Wasp::initSprites()
	{
		if (!_texEnemy.loadFromFile("res/sprites/enemies/wasp.png"))
		{
			cout << "La textura de wasp.png no se ha cargado.\n";
		}
		_sprLoader.setTexture(_texEnemy);
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
		frameWidth = 83;
		frameHeight = 100;
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
	void Wasp::updateAnimations(float deltaTime)
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
	void Wasp::drawAnimations(RenderWindow* window)
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
	void Wasp::accommodateAnimations()
	{
		_boxCollision.setPosition(_renderer.getPosition());
		updateAnimations(0.0f);
	}
	void Wasp::updateAnimationEvents()
	{
		if (_animNormal->getNumberOfFrame() == 2)
		{
			_animNormal->resetAnimation();
			accommodateAnimations();
		}
	}

	void Wasp::moveForward(float deltaTime)
	{
		if (_active && !_defeated)
		{
			_renderer.move(-_speedX * deltaTime, 0.0f);
		}
	}
	void Wasp::moveUpAndDown(float deltaTime)
	{
		if (_active)
		{
			if (!_defeated)
			{
				if (_gravity.actualSpeed + _gravity.acceleration * deltaTime > _maxSpeedY)
				{
					_moveUp = true;
				}
				else if (_gravity.actualSpeed - _gravity.acceleration * deltaTime < -_maxSpeedY)
				{
					_moveUp = false;
				}

				if (_moveUp)
				{
					_gravity.actualSpeed -= _gravity.acceleration * deltaTime;
				}
				else
				{
					_gravity.actualSpeed += _gravity.acceleration * deltaTime;
				}
			}
			else
			{
				_gravity.actualSpeed = (_gravity.actualSpeed + _gravity.acceleration * deltaTime > _gravity.speedLimit) ? _gravity.speedLimit : _gravity.actualSpeed + _gravity.acceleration * deltaTime;
			}

			_renderer.move(0.0f, _gravity.actualSpeed * deltaTime);
		}
	}
}
