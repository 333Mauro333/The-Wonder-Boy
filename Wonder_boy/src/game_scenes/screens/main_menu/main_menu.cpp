#include "main_menu.h"

#include <iostream>

#include "game_manager/game_manager.h"
#include "game_controls/game_controls.h"
#include "scene_manager/scene_manager.h"
#include "game_scenes/levels/0_test/level_test.h"

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
	void MainMenu::update()
	{
		for (int i = 0; i < buttonsSize; i++)
		{
			buttons[i]->update(GameManager::getDeltaTime());
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
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::screenEnter)))
		{
			switch (option)
			{
			case 1:
				SceneManager::loadNewScene(new LevelTest(window));
				break;

			case 2:
				break;

			case 3:
				break;

			case 4:
				window->close();
				break;
			}
		}
	}
	void MainMenu::checkKeyReleased(Keyboard::Key key)
	{

	}

	void MainMenu::init()
	{
		int totalSize = window->getSize().y / 1.5f; // Espacio que va a ocupar toda la lista de botones.
		int firstPosition = window->getSize().y - totalSize; // Posición del primer botón.
		int distanceBetweenButtons = totalSize / buttonsSize; // Diferencia de posiciones (sobre y) entre botones.


		background = RectangleShape(static_cast<Vector2f>(window->getSize())); // Fondo del menú.
		background.setFillColor(sf::Color(0, 180, 0, 255)); // Color verde opaco.

		optionsList[0] = "JUGAR"; // Texto que irá sobre los botones.
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
			buttons[option - 1]->setSelected(false); // Apaga el botón sobre el que se está parado.
			option = (option == 1) ? buttonsSize : --option; // Cambia a la opción anterior (la última si se está sobre la primera).
			buttons[option - 1]->setSelected(true); // Se enciende el nuevo botón.
			break;

		case OPTION_DIRECTION::NEXT:
			buttons[option - 1]->setSelected(false); // Apaga el botón sobre el que se está parado.
			option = (option == buttonsSize) ? 1 : ++option; // Cambia a la opción siguiente (la primera si se está sobre la última).
			buttons[option - 1]->setSelected(true); // Se enciende el nuevo botón.
			break;
		}

		cout << "Opcion actual: " << option << ".\n";
	}
}