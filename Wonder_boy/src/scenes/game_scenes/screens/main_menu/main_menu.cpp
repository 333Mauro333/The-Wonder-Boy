#include "main_menu.h"

#include <iostream>

#include "game_manager/game_manager.h"
#include "controls_manager/controls_manager.h"
#include "scene_manager/scene_manager.h"
#include "curtain_manager/curtain_manager.h"
#include "scenes/game_scenes/screens/credits/credits.h"
#include "scenes/game_scenes/levels/level_1/level_1.h"

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

		if (CurtainManager::screenIsBlack())
		{
			switch (option)
			{
				case 1:
					SceneManager::loadNewScene(new Level1(window));
					break;

				case 3:
					window->close();
					break;
			}
		}

		updateTextColor();
	}
	void MainMenu::draw()
	{
		window->draw(background);

		window->draw(gameTitle);

		for (int i = 0; i < buttonsSize; i++)
		{
			buttons[i]->draw(window);
		}
	}
	void MainMenu::checkKeyPressedOnce(Keyboard::Key key)
	{
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(ControlsManager::screenUp)) && !CurtainManager::isActive())
		{
			changeOption(OPTION_DIRECTION::PREVIOUS);
		}
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(ControlsManager::screenDown)) && !CurtainManager::isActive())
		{
			changeOption(OPTION_DIRECTION::NEXT);
		}
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(ControlsManager::screenEnter))&& !CurtainManager::isActive())
		{
			switch (option)
			{
			case 1:
			case 3:
				CurtainManager::startToCover(CURTAIN_TYPE::FADE);
				break;

			case 2:
				SceneManager::loadNewScene(new Credits(window));
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


		if (!font.loadFromFile("res/fonts/8_bit.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}
		gameTitle.setFont(font);
		gameTitle.setString("WONDER BOY");
		gameTitle.setCharacterSize(85);
		gameTitle.setFillColor(sf::Color::Black);
		gameTitle.setOrigin(gameTitle.getGlobalBounds().width / 2.0f, gameTitle.getGlobalBounds().height / 2.0f);
		gameTitle.setPosition(window->getSize().x / 2.0f, window->getSize().y / 10.0f);
		toBlack = false;

		background = RectangleShape(static_cast<Vector2f>(window->getSize())); // Fondo del menú.
		background.setFillColor(sf::Color(0, 180, 0, 255)); // Color verde opaco.

		optionsList[0] = "PLAY"; // Texto que irá sobre los botones.
		optionsList[1] = "CREDITS";
		optionsList[2] = "QUIT";

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

	void MainMenu::updateTextColor()
	{
		const float maxUint8Value = 255.0f;
		float timeToChangeColor = 0.5f;
		float timePerFrame = maxUint8Value / timeToChangeColor * GameManager::getDeltaTime();
		float r = static_cast<float>(gameTitle.getFillColor().r);
		float g = static_cast<float>(gameTitle.getFillColor().r);


		if (toBlack)
		{
			if (r - timePerFrame <= 0.0f)
			{
				r = 0.0f;
				g = 0.0f;
				toBlack = false;
			}
			else
			{
				r -= timePerFrame;
				g -= timePerFrame;
			}
		}
		else
		{
			if (r + timePerFrame >= maxUint8Value)
			{
				r = maxUint8Value;
				g = maxUint8Value;
				toBlack = true;
			}
			else
			{
				r += timePerFrame;
				g += timePerFrame;
			}
		}

		gameTitle.setFillColor(sf::Color(r, g, gameTitle.getFillColor().b));
	}
}
