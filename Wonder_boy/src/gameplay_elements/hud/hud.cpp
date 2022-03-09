#include "hud.h"

using std::cout;


namespace the_wonder_boy
{
	HUD::HUD(RenderWindow* window, Player* player)
	{
		_window = window;
		_player = player;

		_backHud.setSize(Vector2f(window->getSize().x, window->getSize().y / 5.0f));
		_backHud.setOrigin(_backHud.getGlobalBounds().width / 2.0f, _backHud.getGlobalBounds().height / 2.0f);
		_backHud.setFillColor(sf::Color::Black);
		
		Player::getPoints();

		if (!_texLife.loadFromFile("res/sprites/player/life.png"))
		{
			cout << "La textura life.png no se ha cargado.\n";
		}
		_sprLife.setTexture(_texLife);
		_sprLife.setScale(2.0f, 2.0f);
		_sprLife.setOrigin(_sprLife.getLocalBounds().width / 2.0f, _sprLife.getLocalBounds().height / 2.0f);

		_posZero = { 0.0f, 0.0f };

		if (!_font.loadFromFile("res/fonts/retro.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}
		_textLives.setFont(_font);
		_textLives.setString("X" + toString(static_cast<int>(Player::getLives())));
		_textLives.setCharacterSize(30);
		_textLives.setFillColor(sf::Color::White);
		_textLives.setOrigin(0.0f, _textLives.getGlobalBounds().height);

		_textPoints.setFont(_font);
		_textLives.setString("POINTS: " + toString(static_cast<int>(Player::getPoints())));
		_textLives.setCharacterSize(30);
		_textLives.setFillColor(sf::Color::White);

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
		_backHud.setPosition(Vector2f(_window->getView().getCenter().x, _window->getView().getCenter().y - _window->getView().getSize().y / 2.0f + _backHud.getGlobalBounds().height / 2.0f));

		// Actualizo la posición de la esquina superior derecha de la ventana (ya que la misma se basa en la view y en el backHud).
		_posZero = Vector2f(_window->getView().getCenter().x - _backHud.getGlobalBounds().width / 2.0f, _backHud.getPosition().y - _backHud.getGlobalBounds().height / 2.0f);
		
		// Posiciono los demás elementos dentro del hud.
		// Posición de las vidas.
		float x = _posZero.x + _backHud.getGlobalBounds().width / 10.0f;
		float y = _posZero.y + _backHud.getGlobalBounds().height / 3.0f * 1.9f;

		_sprLife.setPosition(Vector2f(x, y));
		_textLives.setString("X" + toString(static_cast<int>(Player::getLives())));
		_textLives.setPosition(x + _sprLife.getGlobalBounds().width, y + _sprLife.getGlobalBounds().height / 3.0f);

		// Posición del puntaje:
		x = _posZero.x + _backHud.getGlobalBounds().width / 2.5f;
		y = _posZero.y + _backHud.getGlobalBounds().height / 4.0f;
		_textPoints.setString("POINTS: " + toString(static_cast<int>(Player::getPoints())));
		_textPoints.setPosition(x, y);

		Vector2f barSize = { _backHud.getGlobalBounds().width / 2.0f, _backHud.getGlobalBounds().height / 3.0f };
		Vector2f startBar = { _posZero.x + _backHud.getGlobalBounds().width / 2.5f, _posZero.y + _backHud.getGlobalBounds().height / 2.0f };
		float widthRectangleBar = barSize.x / _amountOfRectangles;
		float heightRectangleBar = barSize.y;
		int amountOfColoredRectangles = _player->getHealth() / 3.125f + 1;

		// Barra de vida.
		for (int i = 0; i < _amountOfRectangles; i++)
		{
			_healthBars[i].setSize(Vector2f(widthRectangleBar, heightRectangleBar));
			_healthBars[i].setPosition(startBar.x + widthRectangleBar * i, startBar.y);
			_healthBars[i].setOutlineColor(sf::Color::Black);
			_healthBars[i].setOutlineThickness(-2);
			if (i < 8)
			{
				_healthBars[i].setFillColor(sf::Color(255, 0, 0, 128));
			}
			else
			{
				_healthBars[i].setFillColor(sf::Color(0, 255, 0, 128));
			}
		}
		for (int i = 0; i < amountOfColoredRectangles; i++)
		{
			if (i < _amountOfRectangles && _player->getHealth() > 0.0f)
			{
				_healthBars[i].setFillColor(sf::Color(_healthBars[i].getFillColor().r, _healthBars[i].getFillColor().g, _healthBars[i].getFillColor().b, 255));
			}
		}
	}
	void HUD::draw(RenderWindow* window)
	{
		window->draw(_backHud);
		window->draw(_textLives);
		window->draw(_sprLife);
		window->draw(_textPoints);

		for (int i = 0; i < _amountOfRectangles; i++)
		{
			window->draw(_healthBars[i]);
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
