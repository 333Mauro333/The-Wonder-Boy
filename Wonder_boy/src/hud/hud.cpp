#include "hud.h"

#include <iostream>

using std::cout;



namespace the_wonder_boy
{
	HUD::HUD(RenderWindow* window, Player* player)
	{
		this->window = window;
		this->player = player;

		backHud.setSize(Vector2f(window->getSize().x, window->getSize().y / 5.0f));
		backHud.setOrigin(backHud.getGlobalBounds().width / 2.0f, window->getSize().y / 2.0f);
		backHud.setFillColor(sf::Color::Black);

		cout << "Se ha creado un HUD.\n\n";
	}
	HUD::~HUD()
	{
		cout << "El HUD ha sido eliminado de la memoria.\n\n";
	}

	// Funciones públicas.
	void HUD::update()
	{
		backHud.setPosition(window->getView().getCenter());
	}
	void HUD::draw(RenderWindow* window)
	{
		window->draw(backHud);
	}
}
