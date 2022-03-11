#include "text_string.h"

using std::cout;


namespace the_wonder_boy
{
	Font TextString::_font8Bit;
	Font TextString::_fontRetro;

	TextString::TextString(FONT_TYPE fontType, string text, Vector2f position, Vector2f size, ORIGIN origin, Color color)
	{
		_isVisible = true;

		setFont(fontType);
		setString(text);
		setOrigin(origin);
		setSize(size);
		setPosition(position);
		setColor(color);

		cout << "Se ha creado un texto.\n\n";
	}
	TextString::~TextString()
	{
		cout << "El texto \"" << _text.getString().toAnsiString() << "\" ha sido eliminado de la memoria.\n\n";
	}


	// Funciones públicas.
	void TextString::initFonts()
	{
		if (!_font8Bit.loadFromFile("res/fonts/8_bit.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}

		if (!_fontRetro.loadFromFile("res/fonts/retro.ttf"))
		{
			cout << "No se ha podido cargar la fuente de 8_bit.ttf.\n";
		}
	}
	void TextString::draw(RenderWindow* window)
	{
		if (_isVisible)
		{
			window->draw(_text);
		}
	}

	Text TextString::getText()
	{
		return _text;
	}
	bool TextString::getIsVisible()
	{
		return _isVisible;
	}
	void TextString::setPosition(Vector2f position)
	{
		_text.setPosition(position);
	}
	void TextString::setIsVisible(bool isVisible)
	{
		_isVisible = isVisible;
	}


	// Funciones privadas.
	void TextString::setFont(FONT_TYPE fontType)
	{
		switch (fontType)
		{
		case FONT_TYPE::EIGHT_BIT:
			_text.setFont(_font8Bit);
			break;

		case FONT_TYPE::RETRO:
			_text.setFont(_fontRetro);
			break;
		}
	}
	void TextString::setString(string text)
	{
		_text.setString(text);
	}
	void TextString::setOrigin(ORIGIN origin)
	{
		switch (origin)
		{
		case ORIGIN::CORNER_UP_LEFT:
			_text.setOrigin(0.0f, 0.0f);
			break;

		case ORIGIN::UP_CENTER:
			_text.setOrigin(_text.getGlobalBounds().width / 2.0f, 0.0f);
			break;

		case ORIGIN::CORNER_UP_RIGHT:
			_text.setOrigin(_text.getGlobalBounds().width, 0.0f);
			break;

		case ORIGIN::LEFT_CENTER:
			_text.setOrigin(0.0f, _text.getGlobalBounds().height / 2.0f);
			break;

		case ORIGIN::CENTER:
			_text.setOrigin(_text.getGlobalBounds().width / 2.0f, _text.getGlobalBounds().height / 2.0f);
			break;

		case ORIGIN::RIGHT_CENTER:
			_text.setOrigin(_text.getGlobalBounds().width, _text.getGlobalBounds().height / 2.0f);
			break;

		case ORIGIN::CORNER_DOWN_LEFT:
			_text.setOrigin(0.0f, _text.getGlobalBounds().height);
			break;

		case ORIGIN::DOWN_CENTER:
			_text.setOrigin(_text.getGlobalBounds().width / 2.0f, _text.getGlobalBounds().height);
			break;

		case ORIGIN::CORNER_DOWN_RIGHT:
			_text.setOrigin(_text.getGlobalBounds().width, _text.getGlobalBounds().height);
			break;
		}
	}
	void TextString::setSize(Vector2f size)
	{
		_text.setScale(1.0f / _text.getGlobalBounds().width * size.x, 1.0f / _text.getGlobalBounds().height * size.y);
	}
	void TextString::setColor(Color color)
	{
		_text.setFillColor(color);
	}
}
