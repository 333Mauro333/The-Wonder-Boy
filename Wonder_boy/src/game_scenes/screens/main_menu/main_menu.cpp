#include "main_menu.h"

#include <iostream>

#include "game_controls/game_controls.h"

using std::cout;
using sf::Vector2f;


namespace the_wonder_boy
{
	MainMenu::MainMenu(RenderWindow* window, SELECTED_OPTION selectedOption) : Scene(window)
	{
		cout << "Se ha creado una pantalla de menu principal.\n\n";

		option = static_cast<int>(selectedOption);

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
		for (int i = 0; i < buttonsSize; i++)
		{
			buttons[i]->update(deltaTime);
		}
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
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::screenUp)))
		{
			changeOption(OPTION_DIRECTION::PREVIOUS);
		}
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::screenDown)))
		{
			changeOption(OPTION_DIRECTION::NEXT);
		}
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

		buttons[option - 1]->setSelected(true);
	}
	void MainMenu::destroy()
	{
		for (int i = 0; i < buttonsSize; i++)
		{
			delete buttons[i];
		}
	}

	void MainMenu::changeOption(OPTION_DIRECTION optionDirection)
	{
		switch (optionDirection)
		{
		case OPTION_DIRECTION::PREVIOUS:
			buttons[option - 1]->setSelected(false);
			option = (option == 1) ? buttonsSize : --option;
			buttons[option - 1]->setSelected(true);
			break;

		case OPTION_DIRECTION::NEXT:
			buttons[option - 1]->setSelected(false);
			option = (option == buttonsSize) ? 1 : ++option;
			buttons[option - 1]->setSelected(true);
			break;
		}
	}
}