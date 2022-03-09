#include "sign.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Sign::Sign(float x, float y, SIGN_TYPE signType)
	{
		_signType = signType;

		initSprite(x, y);

		cout << "Se ha creado una senial.\n\n";
	}
	Sign::~Sign()
	{
		cout << "La senial ha sido eliminada de la memoria.\n\n";
	}


	// Funciones públicas.
	void Sign::draw(RenderWindow* window)
	{
		window->draw(_sprSign);
	}

	SIGN_TYPE Sign::getSignType()
	{
		return _signType;
	}
	Sprite Sign::getRenderer()
	{
		return _sprSign;
	}
	void Sign::setPosition(Vector2f position)
	{
		_position = position;
	}


	// Funciones privadas.
	void Sign::initSprite(float x, float y)
	{
		switch (_signType)
		{
		case SIGN_TYPE::FIRST:
			if (!_texSign.loadFromFile("res/sprites/scenes/sign/sign_1.png"))
			{
				cout << "La textura sign_1.png no se ha cargado.\n";
			}
			break;

		case SIGN_TYPE::SECOND:
			if (!_texSign.loadFromFile("res/sprites/scenes/sign/sign_2.png"))
			{
				cout << "La textura sign_2.png no se ha cargado.\n";
			}
			break;

		case SIGN_TYPE::THIRD:
			if (!_texSign.loadFromFile("res/sprites/scenes/sign/sign_3.png"))
			{
				cout << "La textura sign_3.png no se ha cargado.\n";
			}
			break;

		case SIGN_TYPE::FOURTH:
			if (!_texSign.loadFromFile("res/sprites/scenes/sign/sign_4.png"))
			{
				cout << "La textura sign_4.png no se ha cargado.\n";
			}
			break;

		case SIGN_TYPE::GOAL:
			if (!_texSign.loadFromFile("res/sprites/scenes/sign/sign_goal.png"))
			{
				cout << "La textura sign_goal.png no se ha cargado.\n";
			}
			break;
		}

		_sprSign.setTexture(_texSign);
		_sprSign.setOrigin(_sprSign.getGlobalBounds().width / 2.0f, _sprSign.getGlobalBounds().height);
		_sprSign.setPosition(x, y);
	}
}
