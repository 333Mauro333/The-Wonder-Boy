#include "main_menu.h"

#include <iostream>

using std::cout;
using sf::Vector2f;


namespace the_wonder_boy
{
	MainMenu::MainMenu(RenderWindow* window) : Scene(window)
	{
		cout << "Se ha creado una pantalla de menu principal.\n\n";

		init();
	}
	MainMenu::~MainMenu()
	{
		destroy();

		cout << "La pantalla de menu principal ha sido eliminada de la memoria.\n";
	}

	// Funciones públicas.
	void MainMenu::update(float deltaTime)
	{

	}
	void MainMenu::draw()
	{
		window->draw(background);

		for (int i = 0; i < buttonsSize; i++)
		{
			window->draw(buttons[i]);
		}
	}
	void MainMenu::checkKeyPressedOnce(Keyboard::Key key)
	{

	}
	void MainMenu::checkKeyReleased(Keyboard::Key key)
	{

	}

	void MainMenu::init()
	{
		int totalSize = window->getSize().y / 1.5f;
		int firstPosition = window->getSize().y - totalSize;
		int distanceBetweenButtons = totalSize / buttonsSize;


		background = RectangleShape(static_cast<Vector2f>(window->getSize()));
		background.setFillColor(sf::Color(0, 180, 0, 255));

		for (int i = 0; i < buttonsSize; i++)
		{
			buttons[i] = RectangleShape(Vector2f(window->getSize().x / 3.0f, totalSize / (buttonsSize + 2)));
		}
		for (int i = 0; i < buttonsSize; i++)
		{
			buttons[i].setPosition(window->getSize().x / 2.0f, firstPosition); // Hacer una clase para el botón.
			firstPosition += distanceBetweenButtons;
		}
		for (int i = 0; i < buttonsSize; i++)
		{
			buttons[i].setOrigin(buttons[i].getGlobalBounds().width / 2.0f, 0.0f);
			buttons[i].setFillColor(sf::Color(255, 255, 255, 64));
		}
	}
	void MainMenu::destroy()
	{

	}
}