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
		backHud.setOrigin(backHud.getGlobalBounds().width / 2.0f, backHud.getGlobalBounds().height / 2.0f);
		backHud.setFillColor(sf::Color::Black);

		sprLife = player->getLifeSprite();
		sprLife.setScale(1.5f, 1.5f);
		sprLife.setOrigin(sprLife.getLocalBounds().width / 2.0f, sprLife.getLocalBounds().height / 2.0f);

		posZero = { 0.0f, 0.0f };

		cout << "Se ha creado un HUD.\n\n";
	}
	HUD::~HUD()
	{
		cout << "El HUD ha sido eliminado de la memoria.\n\n";
	}

	// Funciones p�blicas.
	void HUD::update()
	{
		// Posici�n correcta, independientemente del tama�o de la ventana.
		backHud.setPosition(Vector2f(window->getView().getCenter().x, window->getView().getCenter().y - window->getView().getSize().y / 2.0f + backHud.getGlobalBounds().height / 2.0f));

		// Actualizo la posici�n de la esquina superior derecha de la ventana (ya que la misma se basa en la view y en el backHud).
		posZero = Vector2f(window->getView().getCenter().x - backHud.getGlobalBounds().width / 2.0f, backHud.getPosition().y - backHud.getGlobalBounds().height / 2.0f);
		
		// Posiciono los dem�s elementos dentro del hud.
		sprLife.setPosition(Vector2f(posZero.x + backHud.getGlobalBounds().width / 8.0f, posZero.y + backHud.getGlobalBounds().height / 3.0f * 2.0f));
	}
	void HUD::draw(RenderWindow* window)
	{
		window->draw(backHud);
		window->draw(sprLife);
	}
}
