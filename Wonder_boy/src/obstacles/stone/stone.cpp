#include "stone.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Stone::Stone(float x, float y)
	{
		initSprites(x, y);

		cout << "Se ha creado una piedra.\n";
	}
	Stone::~Stone()
	{
		cout << "La piedra ha sido eliminada de la memoria.\n\n";
	}

	// Funciones públicas.
	void Stone::draw(RenderWindow* window)
	{
		window->draw(sprStone);

		#if _DEBUG

		window->draw(boxCollision);

		#endif // _DEBUG
	}

	RectangleShape Stone::getBoxCollision()
	{
		return boxCollision;
	}


	// Funciones privadas.
	void Stone::initSprites(float x, float y)
	{
		if (!texStone.loadFromFile("res/sprites/obstacles/stone.png"))
		{
			cout << "La textura stone.png no se ha cargado.\n";
		}

		sprStone.setTexture(texStone);
		sprStone.setOrigin(sprStone.getGlobalBounds().width / 2.0f, sprStone.getGlobalBounds().height);
		sprStone.setPosition(x, y);

		boxCollision.setSize(Vector2f(sprStone.getGlobalBounds().width / 10.0f * 8.0f, sprStone.getGlobalBounds().height / 10.0f * 8.0f));
		boxCollision.setOrigin(boxCollision.getGlobalBounds().width / 2.0f, boxCollision.getGlobalBounds().height);
		boxCollision.setPosition(x, y);
	}
}
