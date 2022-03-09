#include "fruit.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	float Fruit::_timeToDeactivate = 3.0f;

	Fruit::Fruit(float x, float y, FRUIT_TYPE fruitType)
	{
		_fruitType = fruitType;

		_active = false;
		_taken = false;
		_healthValue = 3.125f;
		_pointsValue = 0;
		_counterToDeactivate = _timeToDeactivate;

		switch (fruitType)
		{
		case FRUIT_TYPE::APPLE:
			if (!_texFruit.loadFromFile("res/sprites/items/fruits/apple.png"))
			{
				cout << "La textura de la manzana no se ha cargado.\n";
			}
			_pointsValue = 25;
			break;

		case FRUIT_TYPE::BANANAS:
			if (!_texFruit.loadFromFile("res/sprites/items/fruits/bananas.png"))
			{
				cout << "La textura de las bananas no se ha cargado.\n";
			}
			_pointsValue = 50;
			break;

		case FRUIT_TYPE::CARROT:
			if (!_texFruit.loadFromFile("res/sprites/items/fruits/carrot.png"))
			{
				cout << "La textura de la zanahoria no se ha cargado.\n";
			}
			_pointsValue = 75;
			break;

		case FRUIT_TYPE::TOMATO:
			if (!_texFruit.loadFromFile("res/sprites/items/fruits/tomato.png"))
			{
				cout << "La textura del tomate no se ha cargado.\n";
			}
			_healthValue = 6.25f;
			_pointsValue = 100;
			break;
		}

		_sprFruit.setTexture(_texFruit);
		_sprFruit.setPosition(x, y);
		_sprFruit.setOrigin(_sprFruit.getGlobalBounds().width / 2.0f, _sprFruit.getGlobalBounds().height / 2.0f);

		_boxCollision.setSize(Vector2f(_sprFruit.getGlobalBounds().width, _sprFruit.getGlobalBounds().height));
		_boxCollision.setOrigin(_sprFruit.getGlobalBounds().width / 2.0f, _sprFruit.getGlobalBounds().height / 2.0f);
		_boxCollision.setPosition(x, y);
		_boxCollision.setFillColor(sf::Color(255, 0, 0, 128));

		cout << "Se ha creado una fruta.\n\n";
	}
	Fruit::~Fruit()
	{
		cout << "La fruta ha sido eliminada de la memoria.\n\n";
	}


	// Funciones públicas.
	void Fruit::update(float deltaTime)
	{
		if (_active)
		{
			updateCountdown(deltaTime);
		}
	}
	void Fruit::draw(RenderWindow* window)
	{
		if (_active)
		{
			window->draw(_sprFruit);
		}

		#if _DEBUG

		window->draw(_boxCollision);

		#endif // _DEBUG
	}

	RectangleShape Fruit::getBoxCollision()
	{
		return _boxCollision;
	}
	Vector2f Fruit::getPosition()
	{
		return _sprFruit.getPosition();
	}
	float Fruit::getHealthValue()
	{
		return _healthValue;
	}
	int Fruit::getPointsValue()
	{
		return _pointsValue;
	}
	bool Fruit::isActive()
	{
		return _active;
	}
	bool Fruit::wasTaken()
	{
		return _taken;
	}

	void Fruit::activate()
	{
		_active = true;
	}
	void Fruit::take()
	{
		_active = false;
		_taken = true;
	}

	void Fruit::reset()
	{
		_active = false;
		_taken = false;
		_healthValue = 3.125f;
		_counterToDeactivate = _timeToDeactivate;

		switch (_fruitType)
		{
		case FRUIT_TYPE::APPLE:
			_pointsValue = 25;
			break;

		case FRUIT_TYPE::BANANAS:
			_pointsValue = 50;
			break;

		case FRUIT_TYPE::CARROT:
			_pointsValue = 75;
			break;

		case FRUIT_TYPE::TOMATO:
			_healthValue = 6.25f;
			_pointsValue = 100;
			break;
		}
	}


	// Funciones privadas.
	void Fruit::updateCountdown(float deltaTime)
	{
		if (_counterToDeactivate <= deltaTime)
		{
			_counterToDeactivate = 0.0f;
			_active = false;
			_taken = true;
			cout << "La fruta ha desaparecido.\n";
		}
		else
		{
			_counterToDeactivate -= deltaTime;
		}
	}
}
