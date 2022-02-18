#include "Button.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Button::Button(float x, float y, float w, float h, string optionName) : Entity(x, y)
	{
		isSelected = false;

		// Carga de la imagen del botón.
		if (!texButton.loadFromFile("res/sprites/scenes/main_menu/button.png"))
		{
			cout << "La textura del boton no se ha cargado.\n";
		}
		sprButton.setTexture(texButton);
		sprButton.setOrigin(sprButton.getGlobalBounds().width / 2.0f, sprButton.getGlobalBounds().height / 2.0f);
		sprButton.setScale(1.0f / sprButton.getGlobalBounds().width * w, 1.0f / sprButton.getGlobalBounds().height * h);
		sprButton.setPosition(x, y);

		// Carga del texto que va a ir sobre el botón.
		if (!font.loadFromFile("res/fonts/8_bit.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}
		text.setFont(font);
		text.setString(optionName);
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(h / 1.6575f);
		if (text.getGlobalBounds().width < sprButton.getGlobalBounds().width)
		{
			text.setScale(text.getScale().x, 1.0f / sprButton.getGlobalBounds().height * h);
			text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
		}
		else
		{
			text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
			text.setScale(1.0f / text.getGlobalBounds().width * (w - (w / 20.0f)), 1.0f / sprButton.getGlobalBounds().height * h);
		}
		text.setPosition(x, y);

		cout << "Se ha creado un boton.\n\n";
	}
	Button::~Button()
	{
		cout << "El boton de " << text.getString().toAnsiString() << " ha sido eliminado de la memoria.\n";
	}

	// Funciones públicas.
	void Button::update(float deltaTime)
	{
		if (isSelected)
		{
			sprButton.setColor(sf::Color::White);
		}
		else
		{
			sprButton.setColor(sf::Color(128, 128, 128));
		}
	}
	void Button::draw(RenderWindow* window)
	{
		window->draw(sprButton);
		window->draw(text);
	}

	void Button::setSelected(bool isSelected)
	{
		this->isSelected = isSelected;
	}

	// Funciones privadas
}
