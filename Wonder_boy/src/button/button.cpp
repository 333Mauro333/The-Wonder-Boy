#include "Button.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Button::Button(float x, float y, float w, float h) : Entity(x, y)
	{
		if (!tex.loadFromFile("button.png"))
		{
			cout << "No se pudo cargar el boton.\n";
		}
		spr.setScale(10, 10);

		cout << "Se ha creado un boton.\n\n";
	}
	Button::~Button()
	{
		cout << "El boton ha sido eliminado de la memoria.\n";
	}

	// Funciones privadas.
	void Button::draw(RenderWindow* window)
	{
		window->draw(back);
		window->draw(spr);
	}
}