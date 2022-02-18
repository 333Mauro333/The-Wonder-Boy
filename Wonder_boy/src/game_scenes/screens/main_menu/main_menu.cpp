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

	// Funciones p�blicas.
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
		int totalSize = window->getSize().y / 1.5f; // Espacio que va a ocupar toda la lista de botones.
		int firstPosition = window->getSize().y - totalSize; // Posici�n del primer bot�n.
		int distanceBetweenButtons = totalSize / buttonsSize; // Diferencia de posiciones (sobre y) entre botones.


		background = RectangleShape(static_cast<Vector2f>(window->getSize())); // Fondo del men�.
		background.setFillColor(sf::Color(0, 180, 0, 255)); // Color verde opaco.

		optionsList[0] = "JUGAR"; // Texto que ir� sobre los botones.
		optionsList[1] = "OPCIONES";
		optionsList[2] = "CREDITOS";
		optionsList[3] = "SALIR";

		for (int i = 0; i < buttonsSize; i++)
		{
			buttons[i] = new Button(window->getSize().x / 2.0f, firstPosition, window->getSize().x / 3.0f, totalSize / (buttonsSize + 2), optionsList[i]); // Hacer una clase para el bot�n.
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
			buttons[option - 1]->setSelected(false); // Apaga el bot�n sobre el que se est� parado.
			option = (option == 1) ? buttonsSize : --option; // Cambia a la opci�n anterior (la �ltima si se est� sobre la primera).
			buttons[option - 1]->setSelected(true); // Se enciende el nuevo bot�n.
			break;

		case OPTION_DIRECTION::NEXT:
			buttons[option - 1]->setSelected(false); // Apaga el bot�n sobre el que se est� parado.
			option = (option == buttonsSize) ? 1 : ++option; // Cambia a la opci�n siguiente (la primera si se est� sobre la �ltima).
			buttons[option - 1]->setSelected(true); // Se enciende el nuevo bot�n.
			break;
		}
	}
}