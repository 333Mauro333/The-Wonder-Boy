#include "credits.h"

#include <iostream>

#include "scene_manager/scene_manager.h"
#include "scenes/game_scenes/screens/main_menu/main_menu.h"
#include "controls_manager/controls_manager.h"

using std::cout;


namespace the_wonder_boy
{
	Credits::Credits(RenderWindow* window) : Scene(window)
	{
		cout << "Se ha creado una pantalla de creditos.\n\n";

		init();
	}
	Credits::~Credits()
	{
		cout << "La pantalla de creditos ha sido eliminada de la memoria.\n";
	}


	// Funciones públicas.
	void Credits::update()
	{

	}
	void Credits::draw()
	{
		_window->draw(_background);

		_window->draw(_textProgrammer);
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

	}


	// Funciones privadas.
	void Credits::init()
	{
		_background.setSize(Vector2f(static_cast<float>(_window->getSize().x), static_cast<float>(_window->getSize().y)));
		_background.setFillColor(sf::Color::Magenta);

		if (!_font.loadFromFile("res/fonts/retro.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}
		_textProgrammer.setFont(_font);
		string strCredits = "";
		strCredits += "         Programming:\n\n";
		strCredits += "    Mauro Torres Velasquez\n\n\n";
		strCredits += "            Art:\n\n";
		strCredits += "        Ary Gallués\n";
		strCredits += "    Mauro Torres Velasquez\n";
		strCredits += "     Original game sprites\n\n\n\n";
		strCredits += "Press ENTER to return to menu.";

		_textProgrammer.setString(strCredits);
		_textProgrammer.setCharacterSize(30);
		_textProgrammer.setFillColor(sf::Color::Black);
		_textProgrammer.setOrigin(_textProgrammer.getGlobalBounds().width / 2.0f, _textProgrammer.getGlobalBounds().height / 2.0f);
		_textProgrammer.setPosition(_window->getSize().x / 2.0f, _window->getSize().y / 2.0f);
	}
	void Credits::destroy()
	{

	}
}
