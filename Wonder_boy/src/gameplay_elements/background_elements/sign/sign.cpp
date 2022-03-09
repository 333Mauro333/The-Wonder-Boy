#include "sign.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Sign::Sign(float x, float y, SIGN_TYPE signType)
	{
		this->signType = signType;

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
		window->draw(sprSign);
	}

	SIGN_TYPE Sign::getSignType()
	{
		return signType;
	}
	Sprite Sign::getRenderer()
	{
		return sprSign;
	}
	void Sign::setPosition(Vector2f position)
	{
		this->position = position;
	}


	// Funciones privadas.
	void Sign::initSprite(float x, float y)
	{
		switch (signType)
		{
		case SIGN_TYPE::FIRST:
			if (!texSign.loadFromFile("res/sprites/scenes/sign/sign_1.png"))
			{
				cout << "La textura sign_1.png no se ha cargado.\n";
			}
			break;

		case SIGN_TYPE::SECOND:
			if (!texSign.loadFromFile("res/sprites/scenes/sign/sign_2.png"))
			{
				cout << "La textura sign_2.png no se ha cargado.\n";
			}
			break;

		case SIGN_TYPE::THIRD:
			if (!texSign.loadFromFile("res/sprites/scenes/sign/sign_3.png"))
			{
				cout << "La textura sign_3.png no se ha cargado.\n";
			}
			break;

		case SIGN_TYPE::FOURTH:
			if (!texSign.loadFromFile("res/sprites/scenes/sign/sign_4.png"))
			{
				cout << "La textura sign_4.png no se ha cargado.\n";
			}
			break;

		case SIGN_TYPE::GOAL:
			if (!texSign.loadFromFile("res/sprites/scenes/sign/sign_goal.png"))
			{
				cout << "La textura sign_goal.png no se ha cargado.\n";
			}
			break;
		}

		sprSign.setTexture(texSign);
		sprSign.setOrigin(sprSign.getGlobalBounds().width / 2.0f, sprSign.getGlobalBounds().height);
		sprSign.setPosition(x, y);
	}
}
