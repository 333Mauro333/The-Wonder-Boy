#include "credits.h"

#include <iostream>

#include "scene_manager/scene_manager.h"
#include "scenes/game_scenes/screens/main_menu/main_menu.h"
#include "controls_manager/controls_manager.h"

using std::cout;


namespace the_wonder_boy
{
	Credits::Credits(RenderWindow* window) : Screen(window, 1)
	{
		cout << "Se ha creado una pantalla de creditos.\n\n";

		init();
	}
	Credits::~Credits()
	{
		delete _textProgrammer;

		cout << "La pantalla de creditos ha sido eliminada de la memoria.\n";
	}


	// Funciones públicas.
	void Credits::update()
	{

	}
	void Credits::draw()
	{
		_window->draw(_background);

		_textProgrammer->draw(_window);
	}
	void Credits::checkKeyPressedOnce(Keyboard::Key key)
	{
		if (key == ControlsManager::getKey(WANTED_KEY::SCREEN_ENTER))
		{
			SceneManager::loadNewScene(new MainMenu(_window, SELECTED_OPTION::CREDITS));
		}
	}
	void Credits::checkKeyReleased(Keyboard::Key key)
	{
		key;
	}


	// Funciones privadas.
	void Credits::init()
	{
		initText();
	}
	void Credits::destroy()
	{
		delete _textProgrammer;
	}

	void Credits::initText()
	{
		float windowSizeX = static_cast<float>(_window->getSize().x);
		float windowSizeY = static_cast<float>(_window->getSize().y);
		string strCredits = "";

		_background.setSize(Vector2f(windowSizeX, windowSizeY));
		_background.setFillColor(sf::Color::Magenta);

		strCredits += "         Programming:\n\n";
		strCredits += "    Mauro Torres Velasquez\n\n\n";
		strCredits += "            Art:\n\n";
		strCredits += "        Ary Gallués\n";
		strCredits += "    Mauro Torres Velasquez\n";
		strCredits += "     Original game sprites\n\n\n\n";
		strCredits += "Press ENTER to return to menu.";

		_textProgrammer = new TextString(FONT_TYPE::RETRO, strCredits, Vector2f(windowSizeX / 2.0f, windowSizeY / 2.0f), Vector2f(windowSizeX / 1.25f, windowSizeY / 1.25f), ORIGIN::CENTER);
	}
}
