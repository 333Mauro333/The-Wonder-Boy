#include "game_manager.h"

#include <iostream>
#include <Windows.h>

#include "scene_manager/scene_manager.h"
#include "game_scenes/levels/0_test/level_test.h"

using std::cout;
using sf::Event;


namespace the_wonder_boy
{
	Vector2u GameManager::windowSize; // Menciono la variable estática sólo para evitar un error.

	GameManager::GameManager(unsigned int width, unsigned int height, const std::string windowTitle)
	{
		window = new RenderWindow(sf::VideoMode(width, height), windowTitle); // Creo la ventana.
		windowSize = { width, height }; // Guardo el tamaño de la ventana en una variable Vector2u.
		fps = 60;
		window->setKeyRepeatEnabled(false);

		cout << "Se ha creado un game manager.\n\n";
	}
	GameManager::~GameManager()
	{
		cout << "El game manager ha sido eliminado de la memoria.\n\n";
	}

	void GameManager::run()
	{
		init(); // Inicializa todo.

		// Loop de juego. La condición del while es que esté la ventana del juego abierta.
		while (window->isOpen())
		{
			sf::Clock clock; // Se declara un reloj, cuya cuenta comienza a correr apenas se declara.
			limitFrames();
			float elapsedTime = clock.getElapsedTime().asSeconds(); // Se guarda en una variable el tiempo transcurrido en el frame.

			update(elapsedTime); // Actualiza usando el deltaTime.

			draw(); // Dibuja.
		}

		destroy(); // Destruye.
	}

	Vector2u GameManager::getWindowSize()
	{
		return windowSize;
	}
	void GameManager::setWindowSize(int width, int height)
	{
		windowSize = { static_cast<unsigned int>(width), static_cast<unsigned int>(height) };
	}


	void GameManager::init()
	{
		SceneManager::loadNewScene(new LevelTest(window)); // Inicio la primera escena del juego.
	}
	void GameManager::update(float deltaTime)
	{
		checkEvents(); // Compruebo si hay eventos (cerrar la ventana, presionar una tecla, hacer click, etc).

		SceneManager::getActualScene()->update(deltaTime); // Se "refresca" todo lo que hay en la escena actual.
	}
	void GameManager::draw()
	{
		window->clear(); // Se limpia toda la pantalla (por defecto, de color negro).

		SceneManager::getActualScene()->draw(); // Se dibuja todo lo que hay en la escena actual.

		window->display(); // Muestra todo lo dibujado en la ventana.
	}
	void GameManager::destroy()
	{
		delete SceneManager::getActualScene(); // Se elimina la escena actual para liberar memoria.
	}

	void GameManager::checkEvents()
	{
		Event event;


		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed())
			{
				window->close();
			}

			if (event.type == Event::KeyPressed)
			{
				SceneManager::getActualScene()->checkEvents(event.key.code);
			}
		}
	}

	void GameManager::limitFrames()
	{
		Sleep(1000 / fps);
	}
}
