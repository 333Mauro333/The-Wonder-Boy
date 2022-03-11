#include "Button.h"

using std::cout;


namespace the_wonder_boy
{
	Button::Button(float x, float y, float w, float h, string optionName) : Entity(x, y)
	{
		_selected = false;

		loadButtonSprite(x, y, w, h);
		loadText(x, y, w, h, optionName);

		cout << "Se ha creado un boton.\n\n";
	}
	Button::~Button()
	{
		cout << "El boton ha sido eliminado de la memoria.\n";
		delete _text;
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
		_text->draw(window);
	}

	void Button::setSelected(bool selected)
	{
		_selected = selected;
	}


	// Funciones privadas.
	void Button::loadButtonSprite(float x, float y, float w, float h)
	{
		if (!_texButton.loadFromFile("res/sprites/scenes/main_menu/button.png"))
		{
			cout << "La textura del boton no se ha cargado.\n";
		}
		_sprButton.setTexture(_texButton);
		_sprButton.setOrigin(_sprButton.getGlobalBounds().width / 2.0f, _sprButton.getGlobalBounds().height / 2.0f);
		_sprButton.setScale(1.0f / _sprButton.getGlobalBounds().width * w, 1.0f / _sprButton.getGlobalBounds().height * h);
		_sprButton.setPosition(x, y);
	}
	void Button::loadText(float x, float y, float w, float h, string optionName)
	{
		Text text;
		Font font;
		float widthText = 0.0f;
		float heightText = 0.0f;

		if (!font.loadFromFile("res/fonts/8_bit.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}
		text.setFont(font);

		text.setString(optionName);
		text.setCharacterSize(static_cast<unsigned int>(h / 1.6575f));
		if (text.getGlobalBounds().width < _sprButton.getGlobalBounds().width)
		{
			text.setScale(text.getScale().x, 1.0f / _sprButton.getGlobalBounds().height * h);
		}
		else
		{
			text.setScale(1.0f / text.getGlobalBounds().width * (w - (w / 20.0f)), 1.0f / _sprButton.getGlobalBounds().height * h);
		}

		widthText = text.getGlobalBounds().width;
		heightText = text.getGlobalBounds().height;

		_text = new TextString(FONT_TYPE::EIGHT_BIT, optionName, Vector2f(x, y), Vector2f(widthText, heightText), ORIGIN::CENTER);
	}
}
