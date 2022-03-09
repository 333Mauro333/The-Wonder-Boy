#include "hud.h"

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
		
		Player::getPoints();

		if (!texLife.loadFromFile("res/sprites/player/life.png"))
		{
			cout << "La textura life.png no se ha cargado.\n";
		}
		sprLife.setTexture(texLife);
		sprLife.setScale(2.0f, 2.0f);
		sprLife.setOrigin(sprLife.getLocalBounds().width / 2.0f, sprLife.getLocalBounds().height / 2.0f);

		posZero = { 0.0f, 0.0f };

		if (!font.loadFromFile("res/fonts/retro.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}
		textLives.setFont(font);
		textLives.setString("X" + toString(static_cast<int>(Player::getLives())));
		textLives.setCharacterSize(30);
		textLives.setFillColor(sf::Color::White);
		textLives.setOrigin(0.0f, textLives.getGlobalBounds().height);

		textPoints.setFont(font);
		textLives.setString("POINTS: " + toString(static_cast<int>(Player::getPoints())));
		textLives.setCharacterSize(30);
		textLives.setFillColor(sf::Color::White);

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
		// Posición de las vidas.
		float x = posZero.x + backHud.getGlobalBounds().width / 10.0f;
		float y = posZero.y + backHud.getGlobalBounds().height / 3.0f * 1.9f;

		sprLife.setPosition(Vector2f(x, y));
		textLives.setString("X" + toString(static_cast<int>(Player::getLives())));
		textLives.setPosition(x + sprLife.getGlobalBounds().width, y + sprLife.getGlobalBounds().height / 3.0f);

		// Posición del puntaje:
		x = posZero.x + backHud.getGlobalBounds().width / 2.5f;
		y = posZero.y + backHud.getGlobalBounds().height / 4.0f;
		textPoints.setString("POINTS: " + toString(static_cast<int>(Player::getPoints())));
		textPoints.setPosition(x, y);

		Vector2f barSize = { backHud.getGlobalBounds().width / 2.0f, backHud.getGlobalBounds().height / 3.0f };
		Vector2f startBar = { posZero.x + backHud.getGlobalBounds().width / 2.5f, posZero.y + backHud.getGlobalBounds().height / 2.0f };
		float widthRectangleBar = barSize.x / amountOfRectangles;
		float heightRectangleBar = barSize.y;
		int amountOfColoredRectangles = player->getHealth() / 3.125f + 1;

		// Barra de vida.
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
		window->draw(textLives);
		window->draw(sprLife);
		window->draw(textPoints);

		for (int i = 0; i < amountOfRectangles; i++)
		{
			window->draw(healthBars[i]);
		}
	}


	// Funciones privadas.
	string HUD::toString(int num)
	{
		string stringToReturn = "";
		string stringReverse = "";
		int aux = num;
		int aux2 = 0;


		if (num > 0)
		{
			while (aux > 0)
			{
				aux2 = aux % 10;
				aux /= 10;
				stringReverse.push_back(static_cast<char>(aux2 + 48));
			}
		}
		else
		{
			return "0";
		}

		stringToReturn = stringReverse;

		for (int i = 0; i < stringReverse.size(); i++)
		{
			int j = (stringReverse.size() - 1) - i;
			stringToReturn[i] = stringReverse[j];
		}

		return stringToReturn;
	}
}
