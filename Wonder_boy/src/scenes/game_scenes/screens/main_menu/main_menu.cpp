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
using sf::Uint8;


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
			buttons[i]->update();
		}

		if (CurtainManager::screenIsBlack())
		{
			switch (option)
			{
				case 1:
					SceneManager::loadNewScene(new Level1(_window));
					break;

				case 3:
					_window->close();
					break;
			}
		}

		updateTextColor();
	}
	void MainMenu::draw()
	{
		_window->draw(background);

		_window->draw(gameTitle);

		for (int i = 0; i < buttonsSize; i++)
		{
			buttons[i]->draw(_window);
		}
	}
	void MainMenu::checkKeyPressedOnce(Keyboard::Key key)
	{
		if (key == ControlsManager::getKey(WANTED_KEY::SCREEN_UP) && !CurtainManager::isActive())
		{
			changeOption(OPTION_DIRECTION::PREVIOUS);
		}
		if (key == ControlsManager::getKey(WANTED_KEY::SCREEN_DOWN) && !CurtainManager::isActive())
		{
			changeOption(OPTION_DIRECTION::NEXT);
		}
		if (key == ControlsManager::getKey(WANTED_KEY::SCREEN_ENTER) && !CurtainManager::isActive())
		{
			switch (option)
			{
			case 1:
			case 3:
				CurtainManager::startToCover(CURTAIN_TYPE::FADE);
				break;

			case 2:
				SceneManager::loadNewScene(new Credits(_window));
				break;
			}
		}
	}
	void MainMenu::checkKeyReleased(Keyboard::Key key)
	{
		key;
	}

	void MainMenu::init()
	{
		int totalSize = static_cast<int>(_window->getSize().y / 1.5f); // Espacio que va a ocupar toda la lista de botones.
		int firstPosition = _window->getSize().y - totalSize; // Posición del primer botón.
		int distanceBetweenButtons = totalSize / buttonsSize; // Diferencia de posiciones (sobre y) entre botones.
		Vector2f desiredSize = { static_cast<float>(_window->getSize().x) / 2.0f, static_cast<float>(_window->getSize().y) / 8.0f };

		// Averiguar cómo funcionan los valores de la ventana al cambiar el tamaño. Mostrar couts con TODA la info al presionar
		// una tecla.
		background.setSize(static_cast<Vector2f>(_window->getSize()));
		background.setSize(Vector2f(static_cast<float>(_window->getSize().x), static_cast<float>(_window->getSize().y)));
		background.setOrigin(static_cast<float>(background.getGlobalBounds().width) / 2.0f, background.getGlobalBounds().height / 2.0f);
		background.setPosition(static_cast<float>(_window->getSize().x) / 2.0f, static_cast<float>(_window->getSize().y) / 2.0f);
		background.setFillColor(sf::Color(0, 180, 0, 255)); // Color verde opaco.

		if (!font.loadFromFile("res/fonts/8_bit.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}
		gameTitle.setFont(font);
		gameTitle.setString("WONDER BOY");
		gameTitle.setOrigin(gameTitle.getGlobalBounds().width / 2.0f, gameTitle.getGlobalBounds().height / 2.0f);
		gameTitle.setScale(1.0f / gameTitle.getGlobalBounds().width * desiredSize.x, 1.0f / gameTitle.getGlobalBounds().height * desiredSize.y);
		gameTitle.setPosition(_window->getSize().x / 2.0f, _window->getSize().y / 10.0f);
		gameTitle.setFillColor(sf::Color::Black);
		toBlack = false;


		optionsList[0] = "PLAY"; // Texto que irá sobre los botones.
		optionsList[1] = "CREDITS";
		optionsList[2] = "QUIT";

		for (int i = 0; i < buttonsSize; i++)
		{
			buttons[i] = new Button(static_cast<float>(_window->getSize().x) / 2.0f, static_cast<float>(firstPosition), static_cast<float>(_window->getSize().x) / 3.0f, static_cast<float>(totalSize / (buttonsSize + 2)), optionsList[i]); // Hacer una clase para el botón.
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

		gameTitle.setFillColor(sf::Color(static_cast<Uint8>(r), static_cast<Uint8>(g), gameTitle.getFillColor().b));
	}
}
