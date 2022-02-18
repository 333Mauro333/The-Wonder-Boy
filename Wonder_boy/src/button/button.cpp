#include "Button.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Button::Button(float x, float y, float w, float h, string optionName) : Entity(x, y)
	{
		if (!texButton.loadFromFile("res/button.png"))
		{
			cout << "No se pudo cargar el boton.\n";
		}
		sprButton.setTexture(texButton);
		sprButton.setOrigin(sprButton.getGlobalBounds().width / 2.0f, sprButton.getGlobalBounds().height / 2.0f);
		sprButton.setScale(1.0f / sprButton.getGlobalBounds().width * w, 1.0f / sprButton.getGlobalBounds().height * h);
		sprButton.setPosition(x, y);

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
		cout << "El boton ha sido eliminado de la memoria.\n";
	}

	// Funciones públicas.
	void Button::draw(RenderWindow* window)
	{
		window->draw(back);
		window->draw(sprButton);
		window->draw(text);
	}
}
