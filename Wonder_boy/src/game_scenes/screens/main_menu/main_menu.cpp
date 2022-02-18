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
			buttons[i]->draw(window);
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

		optionsList[0] = "JUGAR";
		optionsList[1] = "OPCIONES";
		optionsList[2] = "CREDITOS";
		optionsList[3] = "SALIR";

		for (int i = 0; i < buttonsSize; i++)
		{
			buttons[i] = new Button(window->getSize().x / 2.0f, firstPosition, window->getSize().x / 3.0f, totalSize / (buttonsSize + 2), optionsList[i]); // Hacer una clase para el botón.
			firstPosition += distanceBetweenButtons;
		}
	}
	void MainMenu::destroy()
	{
		for (int i = 0; i < buttonsSize; i++)
		{
			delete buttons[i];
		}
	}
}