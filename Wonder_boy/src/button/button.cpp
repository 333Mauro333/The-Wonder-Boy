#include "Button.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Button::Button(float x, float y, float w, float h, string optionName) : Entity(x, y)
	{
		_selected = false;

		// Carga de la imagen del botón.
		if (!_texButton.loadFromFile("res/sprites/scenes/main_menu/button.png"))
		{
			cout << "La textura del boton no se ha cargado.\n";
		}
		_sprButton.setTexture(_texButton);
		_sprButton.setOrigin(_sprButton.getGlobalBounds().width / 2.0f, _sprButton.getGlobalBounds().height / 2.0f);
		_sprButton.setScale(1.0f / _sprButton.getGlobalBounds().width * w, 1.0f / _sprButton.getGlobalBounds().height * h);
		_sprButton.setPosition(x, y);

		// Carga del texto que va a ir sobre el botón.
		if (!_font.loadFromFile("res/fonts/8_bit.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}
		_text.setFont(_font);
		_text.setString(optionName);
		_text.setFillColor(sf::Color::Black);
		_text.setCharacterSize(static_cast<unsigned int>(h / 1.6575f));
		if (_text.getGlobalBounds().width < _sprButton.getGlobalBounds().width)
		{
			_text.setScale(_text.getScale().x, 1.0f / _sprButton.getGlobalBounds().height * h);
			_text.setOrigin(_text.getGlobalBounds().width / 2.0f, _text.getGlobalBounds().height / 2.0f);
		}
		else
		{
			_text.setOrigin(_text.getGlobalBounds().width / 2.0f, _text.getGlobalBounds().height / 2.0f);
			_text.setScale(1.0f / _text.getGlobalBounds().width * (w - (w / 20.0f)), 1.0f / _sprButton.getGlobalBounds().height * h);
		}
		_text.setPosition(x, y);

		cout << "Se ha creado un boton.\n\n";
	}
	Button::~Button()
	{
		cout << "El boton de " << _text.getString().toAnsiString() << " ha sido eliminado de la memoria.\n";
	}

	// Funciones públicas.
	void Button::update()
	{
		if (_selected)
		{
			_sprButton.setColor(sf::Color::White);
		}
		else
		{
			_sprButton.setColor(sf::Color(128, 128, 128));
		}
	}
	void Button::draw(RenderWindow* window)
	{
		window->draw(_sprButton);
		window->draw(_text);
	}

	void Button::setSelected(bool selected)
	{
		_selected = selected;
	}
}
