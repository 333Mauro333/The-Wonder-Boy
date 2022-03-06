#include "platform.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Platform::Platform(float x, float y) : Entity(x, y)
	{
		if (!texPlatform.loadFromFile("res/sprites/scenes/level_test/platform.png"))
		{
			cout << "La textura platform.png no se ha cargado.\n";
		}

		sprPlatform.setTexture(texPlatform);
		sprPlatform.setOrigin(sprPlatform.getGlobalBounds().width / 2.0f, 0.0f);
		sprPlatform.setPosition(x, y);

		boxCollision.setSize(Vector2f(sprPlatform.getGlobalBounds().width, sprPlatform.getGlobalBounds().height / 2.0f));
		boxCollision.setOrigin(sprPlatform.getGlobalBounds().width / 2.0f, 0.0f);
		boxCollision.setPosition(x, y);
		boxCollision.setFillColor(sf::Color(255, 0, 0, 128));

		cout << "Se ha creado una plataforma.\n\n";
	}
	Platform::~Platform()
	{
		cout << "La plataforma ha sido eliminada de la memoria.\n";
	}


	// Funciones públicas.
	void Platform::draw(RenderWindow* window)
	{
		window->draw(sprPlatform);

		#if _DEBUG

		window->draw(boxCollision);

		#endif // _DEBUG
	}

	RectangleShape Platform::getBoxCollision()
	{
		return boxCollision;
	}

}
