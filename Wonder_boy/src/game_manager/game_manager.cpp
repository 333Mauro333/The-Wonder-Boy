#include "game_manager.h"

#include <iostream>

#include "scene_manager/scene_manager.h"
#include "game_scenes/levels/0_test/level_test.h"

using std::cout;


namespace the_wonder_boy
{
	Vector2u GameManager::windowSize;

	GameManager::GameManager(unsigned int width, unsigned int height, const std::string windowTitle)
	{
		window = new RenderWindow(sf::VideoMode(width, height), windowTitle);
		windowSize = { width, height };

		cout << "Se ha creado un game manager.\n\n";
	}
	GameManager::~GameManager()
	{
		cout << "El game manager ha sido eliminado de la memoria.\n\n";
	}

	void GameManager::run()
	{
		init();

		while (window->isOpen())
		{
			sf::Clock clock;
			float elapsedTime = clock.getElapsedTime().asSeconds();

			update(elapsedTime);

			draw();
		}

		destroy();
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
		SceneManager::loadNewScene(new LevelTest(window));
	}
	void GameManager::update(float deltaTime)
	{
		checkEvents();

		SceneManager::getActualScene()->update(deltaTime);
	}
	void GameManager::draw()
	{
		window->clear();

		SceneManager::getActualScene()->draw();

		window->display();
	}
	void GameManager::destroy()
	{
		if (SceneManager::getActualScene() != NULL)
		{
			delete SceneManager::getActualScene();
		}
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
