#include "stone_hammer.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	GRAVITY StoneHammer::_baseGravity = { 50.0f, 750.0f, 500.0f, false };
	const float StoneHammer::_xSpeed = 1200.0f;

	StoneHammer::StoneHammer() : Entity(0.0f, 0.0f)
	{
		_animationState = ANIMATION_STATE_HAMMER::THROWN_RIGHT;
		_isThrown = false;

		initAnimations();

		_boxCollision.setFillColor(sf::Color(255, 0, 0, 128));
		_boxCollision.setSize(Vector2f(63.0f, 63.0f));
		_boxCollision.setOrigin(_boxCollision.getGlobalBounds().width / 2.0f, _boxCollision.getGlobalBounds().height / 2.0f);

		_gravity = _baseGravity;

		cout << "Se ha creado un martillo de piedra.\n\n";
	}
	StoneHammer::~StoneHammer()
	{
		delete _animThrownRight;
		delete _animThrownLeft;

		cout << "El martillo de piedra ha sido eliminado de la memoria.\n\n";
	}


	// Funciones públicas.
	void StoneHammer::update(float deltaTime)
	{
		if (_isThrown)
		{
			gravityForce(deltaTime);
			if (_animationState == ANIMATION_STATE_HAMMER::THROWN_RIGHT)
			{
				_renderer.move(_xSpeed * deltaTime, 0.0f);
			}
			else if (_animationState == ANIMATION_STATE_HAMMER::THROWN_LEFT)
			{
				_renderer.move(-_xSpeed * deltaTime, 0.0f);
			}
			updateAnimations(deltaTime);
			accommodateAnimations();
		}
	}
	void StoneHammer::draw(RenderWindow* window)
	{
		drawAnimations(window);

		#if _DEBUG

		window->draw(_boxCollision);

		#endif // _DEBUG
	}

	RectangleShape StoneHammer::getBoxCollision()
	{
		return _boxCollision;
	}
	bool StoneHammer::getIsThrown()
	{
		return _isThrown;
	}
	Vector2f StoneHammer::getPosition()
	{
		return _renderer.getPosition();
	}
	void StoneHammer::setPosition(float x, float y)
	{
		_renderer.setPosition(x, y);
	}

	void StoneHammer::throwIt(THROW_DIRECTION throwDirection)
	{
		if (!_isThrown)
		{
			_isThrown = true;

			switch (throwDirection)
			{
			case THROW_DIRECTION::LEFT:
				_animationState = ANIMATION_STATE_HAMMER::THROWN_LEFT;
				break;

			case THROW_DIRECTION::RIGHT:
				_animationState = ANIMATION_STATE_HAMMER::THROWN_RIGHT;
				break;
			}

			accommodateAnimations();
		}
	}
	void StoneHammer::hit()
	{
		_isThrown = false;
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

		if (!_texThrownRight.loadFromFile("res/sprites/player/stone_hammer_right.png"))
		{
			cout << "La textura stone_hammer_right.png no se ha cargado.\n";
		}
		_sprLoader.setTexture(_texThrownRight);
		_sprLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight / 2));
		_animThrownRight = new Animation(_sprLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animThrownRight->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion

		#pragma region LANZADO HACIA LA DERECHA

		if (!_texThrownLeft.loadFromFile("res/sprites/player/stone_hammer_left.png"))
		{
			cout << "La textura stone_hammer_left.png no se ha cargado.\n";
		}
		_sprLoader.setTexture(_texThrownLeft);
		_sprLoader.setOrigin(frameWidth / 2.0f, static_cast<float>(frameHeight / 2));
		_animThrownLeft = new Animation(_sprLoader, ANIMATION_MODE::LOOP);
		for (int i = 0; i < amountOfFrames; i++)
		{
			IntRect intRect = IntRect(left, 0, frameWidth, frameHeight);
			Frame* frame = new Frame(intRect, frameDuration);

			_animThrownLeft->addFrame(frame);
			left += frameWidth;
		}
		left = 0;

		#pragma endregion
	}
	void StoneHammer::updateAnimations(float deltaTime)
	{
		switch (_animationState)
		{
		case ANIMATION_STATE_HAMMER::THROWN_RIGHT:
			_animThrownRight->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animThrownRight->update(deltaTime);
			break;

		case ANIMATION_STATE_HAMMER::THROWN_LEFT:
			_animThrownLeft->_target.setPosition(_renderer.getPosition().x, _renderer.getPosition().y);
			_animThrownLeft->update(deltaTime);
			break;
		}
	}
	void StoneHammer::drawAnimations(RenderWindow* window)
	{
		if (_isThrown)
		{
			switch (_animationState)
			{
			case ANIMATION_STATE_HAMMER::THROWN_RIGHT:
				window->draw(_animThrownRight->_target);
				break;

			case ANIMATION_STATE_HAMMER::THROWN_LEFT:
				window->draw(_animThrownLeft->_target);
				break;
			}
		}
	}
	void StoneHammer::accommodateAnimations()
	{
		_boxCollision.setPosition(_renderer.getPosition());
		updateAnimations(0.0f);
	}
	
	void StoneHammer::gravityForce(float deltaTime)
	{
		_gravity.actualSpeed = (_gravity.actualSpeed + _gravity.acceleration * deltaTime > _gravity.speedLimit) ? _gravity.speedLimit : _gravity.actualSpeed + _gravity.acceleration * deltaTime;

		_renderer.move(0.0f, _gravity.actualSpeed * deltaTime);
	}

	void StoneHammer::resetValues()
	{
		_gravity = _baseGravity;
	}
}
