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

	// Funciones públicas.
	void HUD::update()
	{
		// Posición correcta, independientemente del tamaño de la ventana.
		backHud.setPosition(Vector2f(window->getView().getCenter().x, window->getView().getCenter().y - window->getView().getSize().y / 2.0f + backHud.getGlobalBounds().height / 2.0f));

		// Actualizo la posición de la esquina superior derecha de la ventana (ya que la misma se basa en la view y en el backHud).
		posZero = Vector2f(window->getView().getCenter().x - backHud.getGlobalBounds().width / 2.0f, backHud.getPosition().y - backHud.getGlobalBounds().height / 2.0f);
		
		// Posiciono los demás elementos dentro del hud.
		sprLife.setPosition(Vector2f(posZero.x + backHud.getGlobalBounds().width / 8.0f, posZero.y + backHud.getGlobalBounds().height / 3.0f * 2.0f));
		Vector2f barSize = { backHud.getGlobalBounds().width / 2.0f, backHud.getGlobalBounds().height / 2.5f };
		Vector2f startBar = { posZero.x + backHud.getGlobalBounds().width / 3.5f, posZero.y + backHud.getGlobalBounds().height / 1.5f };
		float widthRectangleBar = barSize.x / amountOfRectangles;
		float heightRectangleBar = barSize.y;
		int amountOfColoredRectangles = player->getHealth() / 3.125f + 1;
		for (int i = 0; i < amountOfRectangles; i++)
		{
			healthBars[i].setSize(Vector2f(widthRectangleBar, heightRectangleBar));
			healthBars[i].setPosition(startBar.x + widthRectangleBar * i, startBar.y);
			healthBars[i].setOutlineColor(sf::Color::Black);
			healthBars[i].setOutlineThickness(-2);
			if (i < 8)
			{
				healthBars[i].setFillColor(sf::Color(255, 0, 0, 128));
			}
			else
			{
				healthBars[i].setFillColor(sf::Color(0, 255, 0, 128));
			}
		}
		for (int i = 0; i < amountOfColoredRectangles; i++)
		{
			if (i < amountOfRectangles && player->getHealth() > 0.0f)
			{
				healthBars[i].setFillColor(sf::Color(healthBars[i].getFillColor().r, healthBars[i].getFillColor().g, healthBars[i].getFillColor().b, 255));
			}
		}
	}
	void HUD::draw(RenderWindow* window)
	{
		window->draw(backHud);
		window->draw(sprLife);
		for (int i = 0; i < amountOfRectangles; i++)
		{
			window->draw(healthBars[i]);
		}
	}
}
