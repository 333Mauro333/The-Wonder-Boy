#include "credits.h"

#include <iostream>

#include "scene_manager/scene_manager.h"
#include "game_scenes/screens/main_menu/main_menu.h"
#include "game_controls/game_controls.h"

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
		window->draw(background);

		window->draw(textProgrammer);
	}
	void Credits::checkKeyPressedOnce(Keyboard::Key key)
	{
		if (Keyboard::isKeyPressed(static_cast<Keyboard::Key>(GameControls::screenEnter)))
		{
			SceneManager::loadNewScene(new MainMenu(window, SELECTED_OPTION::CREDITS));
		}
	}
	void Credits::checkKeyReleased(Keyboard::Key key)
	{

	}


	// Funciones privadas.
	void Credits::init()
	{
		background.setSize(Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
		background.setFillColor(sf::Color::Magenta);

		if (!font.loadFromFile("res/fonts/8_bit.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}
		textProgrammer.setFont(font);
		textProgrammer.setString("                Programmer:\n\n      Mauro Torres Velasquez\n\n\n                     Artists:\n\n                 Ary Gallues\n      Mauro Torres Velasquez\n         Original game sprites\n\n\n\nPress ENTER to return to menu");
		textProgrammer.setCharacterSize(30);
		textProgrammer.setFillColor(sf::Color::Black);
		textProgrammer.setOrigin(textProgrammer.getGlobalBounds().width / 2.0f, textProgrammer.getGlobalBounds().height / 2.0f);
		textProgrammer.setPosition(window->getSize().x / 2.0f, window->getSize().y / 2.0f);
	}
	void Credits::destroy()
	{

	}
}
