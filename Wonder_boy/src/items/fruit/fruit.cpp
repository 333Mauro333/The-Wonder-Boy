#include "fruit.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	float Fruit::timeToDeactivate = 3.0f;

	Fruit::Fruit(float x, float y, FRUIT_TYPE fruitType)
	{
		this->fruitType = fruitType;

		active = false;
		taken = false;
		healthValue = 3.125f;
		pointsValue = 0;
		counterToDeactivate = timeToDeactivate;

		switch (fruitType)
		{
		case FRUIT_TYPE::APPLE:
			if (!texFruit.loadFromFile("res/sprites/items/fruits/apple.png"))
			{
				cout << "La textura de la manzana no se ha cargado.\n";
			}
			pointsValue = 25;
			break;

		case FRUIT_TYPE::BANANAS:
			if (!texFruit.loadFromFile("res/sprites/items/fruits/bananas.png"))
			{
				cout << "La textura de las bananas no se ha cargado.\n";
			}
			pointsValue = 50;
			break;

		case FRUIT_TYPE::CARROT:
			if (!texFruit.loadFromFile("res/sprites/items/fruits/carrot.png"))
			{
				cout << "La textura de la zanahoria no se ha cargado.\n";
			}
			pointsValue = 75;
			break;

		case FRUIT_TYPE::TOMATO:
			if (!texFruit.loadFromFile("res/sprites/items/fruits/tomato.png"))
			{
				cout << "La textura del tomate no se ha cargado.\n";
			}
			healthValue = 6.25f;
			pointsValue = 100;
			break;
		}

		sprFruit.setTexture(texFruit);
		sprFruit.setPosition(x, y);
		sprFruit.setOrigin(sprFruit.getGlobalBounds().width / 2.0f, sprFruit.getGlobalBounds().height / 2.0f);

		boxCollision.setSize(Vector2f(sprFruit.getGlobalBounds().width, sprFruit.getGlobalBounds().height));
		boxCollision.setOrigin(sprFruit.getGlobalBounds().width / 2.0f, sprFruit.getGlobalBounds().height / 2.0f);
		boxCollision.setPosition(x, y);
		boxCollision.setFillColor(sf::Color(255, 0, 0, 128));

		cout << "Se ha creado una fruta.\n\n";
	}
	Fruit::~Fruit()
	{
		cout << "La fruta ha sido eliminada de la memoria.\n\n";
	}


	// Funciones públicas.
	void Fruit::update(float deltaTime)
	{
		if (active)
		{
			updateCountdown(deltaTime);
		}
	}
	void Fruit::draw(RenderWindow* window)
	{
		if (active)
		{
			window->draw(sprFruit);
		}

		#if _DEBUG

		window->draw(boxCollision);

		#endif // _DEBUG
	}

	RectangleShape Fruit::getBoxCollision()
	{
		return boxCollision;
	}
	Vector2f Fruit::getPosition()
	{
		return sprFruit.getPosition();
	}
	bool Fruit::isActive()
	{
		return active;
	}
	bool Fruit::wasTaken()
	{
		return taken;
	}
	float Fruit::getHealthValue()
	{
		return healthValue;
	}
	int Fruit::getPointsValue()
	{
		return pointsValue;
	}

	void Fruit::activate()
	{
		active = true;
	}
	void Fruit::take()
	{
		active = false;
		taken = true;
	}

	void Fruit::reset()
	{
		active = false;
		taken = false;
		healthValue = 3.125f;
		counterToDeactivate = timeToDeactivate;

		switch (fruitType)
		{
		case FRUIT_TYPE::APPLE:
			pointsValue = 25;
			break;

		case FRUIT_TYPE::BANANAS:
			pointsValue = 50;
			break;

		case FRUIT_TYPE::CARROT:
			pointsValue = 75;
			break;

		case FRUIT_TYPE::TOMATO:
			healthValue = 6.25f;
			pointsValue = 100;
			break;
		}
	}


	// Funciones privadas.
	void Fruit::updateCountdown(float deltaTime)
	{
		if (counterToDeactivate <= deltaTime)
		{
			counterToDeactivate = 0.0f;
			active = false;
			taken = true;
			cout << "La fruta ha desaparecido.\n";
		}
		else
		{
			counterToDeactivate -= deltaTime;
		}
	}
}
