#include "game_manager.h"

#include <iostream>
#include <Windows.h>

#include "scene_manager/scene_manager.h"
#include "curtain_manager/curtain_manager.h"
#include "game_scenes/screens/main_menu/main_menu.h"
#include "game_scenes/levels/1_gameplay/gameplay_1.h"

using std::cout;
using sf::Event;
using sf::Image;


namespace the_wonder_boy
{
	Vector2u GameManager::windowSize; // Menciono la variable est�tica s�lo para evitar un error.

	float GameManager::deltaTime = 0.0f;

	GameManager::GameManager(unsigned int width, unsigned int height, const std::string windowTitle)
	{
		Image icon = Image();
		if (!icon.loadFromFile("res/sprites/game_icon.png"))
		{
			cout << "El icono no ha sido cargado.\n";
		}

		window = new RenderWindow(sf::VideoMode(width, height), windowTitle); // Creo la ventana.
		windowSize = { width, height }; // Guardo el tama�o de la ventana en una variable Vector2u.
		fps = 60;
		window->setKeyRepeatEnabled(false); // Deshabilita el repetimiento de una tecla al mantenerse presionada (aplica para
		// el evento de obtener la tecla en el momento que fue presionada).
		window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		cout << "Se ha creado un game manager.\n\n";
	}
	GameManager::~GameManager()
	{
		cout << "El game manager ha sido eliminado de la memoria.\n\n";
	}

	// Funciones p�blicas.
	void GameManager::run()
	{
		init(); // Inicializa.

		// Loop de juego. La condici�n del while es que est� la ventana del juego abierta.
		while (window->isOpen())
		{
			sf::Clock clock; // Se declara un reloj, cuya cuenta comienza a correr apenas se declara.
			limitFrames(); // Funci�n para simular un deltaTime, ya que el propio de la ventana es propenso a imprecisiones.
			deltaTime = clock.getElapsedTime().asSeconds(); // Se guarda en una variable el tiempo transcurrido en el frame.

			update(); // Actualiza usando el deltaTime.

			draw(); // Dibuja.
		}

		destroy(); // Destruye todos los elementos del nivel, incluyendo el mismo.
	}

	Vector2u GameManager::getWindowSize()
	{
		return windowSize;
	}
	void GameManager::setWindowSize(int width, int height)
	{
		windowSize = { static_cast<unsigned int>(width), static_cast<unsigned int>(height) };
	}

	float GameManager::getDeltaTime()
	{
		return deltaTime;
	}


	// Funciones privadas.
	void GameManager::init()
	{
		CurtainManager::initValues(windowSize);

		SceneManager::loadNewScene(new MainMenu(window, SELECTED_OPTION::PLAY)); // Inicio la primera escena del juego.
	}
	void GameManager::update()
	{
		checkEvents(); // Compruebo si hay eventos (cerrar la ventana, presionar una tecla, hacer click, etc).

		CurtainManager::update(deltaTime); // Actualizo la cortina entre escenas durante toda la ejecuci�n.

		SceneManager::getActualScene()->update(); // Se actualiza todo lo que hay en la escena actual.
	}
	void GameManager::draw()
	{
		window->clear(); // Se limpia toda la pantalla (por defecto, de color negro).

		SceneManager::getActualScene()->draw(); // Se dibuja todo lo que hay en la escena actual.

		CurtainManager::draw(window);

		window->display(); // Se muestra en la ventana todo lo dibujado.
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
			if (event.type == Event::Closed)
			{
				window->close(); // Cierra la ventana.
			}

			if (event.type == Event::KeyPressed)
			{
				// Env�a a la escena actual la tecla soltada y comprueba reacciones en base a esa tecla soltada.
				SceneManager::getActualScene()->checkKeyPressedOnce(event.key.code);
			}

			if (event.type == Event::KeyReleased)
			{
				// Env�a a la escena actual la tecla soltada y comprueba reacciones en base a esa tecla soltada.
				SceneManager::getActualScene()->checkKeyReleased(event.key.code);
			}
		}
	}

	void GameManager::limitFrames()
	{
		Sleep(1000 / fps);
	}
}
