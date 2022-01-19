#include "game_manager.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	GameManager::GameManager(unsigned int width, unsigned int height, const std::string windowTitle)
	{
		window = new RenderWindow(sf::VideoMode(width, height), windowTitle);

		cout << "Se ha creado un game manager.\n\n";
	}
	GameManager::~GameManager()
	{
		cout << "El game manager ha sido eliminado de la memoria.\n\n";
	}

	void GameManager::run()
	{
		// Se llama al iniciado de la primera escena.

		while (window->isOpen())
		{
			sf::Clock clock;
			float elapsedTime = clock.getElapsedTime().asSeconds();

			// update
			// draw
		}

		// destroy
	}

	void GameManager::init()
	{
		// Carga de la primera escena.
	}
	void GameManager::update(float deltaTime)
	{
		checkEvents();

		// Update de la escena actual.
	}
	void GameManager::draw()
	{
		window->clear();

		// Se dibuja la escena actual.

		window->display();
	}
	void GameManager::destroy()
	{
		// Se destruye la escena actual.
	}

	void GameManager::checkEvents()
	{
		sf::Event event;

		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed())
			{
				window->close();
			}
		}
	}
}