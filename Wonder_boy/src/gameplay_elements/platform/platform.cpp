#include "platform.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Platform::Platform(float x, float y) : Entity(x, y)
	{
		if (!_texPlatform.loadFromFile("res/sprites/scenes/level_test/platform.png"))
		{
			cout << "La textura platform.png no se ha cargado.\n";
		}
		_sprPlatform.setTexture(_texPlatform);
		_sprPlatform.setOrigin(_sprPlatform.getGlobalBounds().width / 2.0f, 0.0f);
		_sprPlatform.setPosition(x, y);

		_boxCollision.setSize(Vector2f(_sprPlatform.getGlobalBounds().width, _sprPlatform.getGlobalBounds().height / 2.0f));
		_boxCollision.setOrigin(_sprPlatform.getGlobalBounds().width / 2.0f, 0.0f);
		_boxCollision.setPosition(x, y);
		_boxCollision.setFillColor(sf::Color(255, 0, 0, 128));

		cout << "Se ha creado una plataforma.\n\n";
	}
	Platform::~Platform()
	{
		cout << "La plataforma ha sido eliminada de la memoria.\n";
	}


	// Funciones públicas.
	void Platform::draw(RenderWindow* window)
	{
		window->draw(_sprPlatform);

		#if _DEBUG

		window->draw(_boxCollision);

		#endif // _DEBUG
	}

	RectangleShape Platform::getBoxCollision()
	{
		return _boxCollision;
	}
}
