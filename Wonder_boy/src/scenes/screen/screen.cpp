#include "screen.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Screen::Screen(RenderWindow* window, int maxOption) : Scene(window)
	{
		cout << "Se ha creado una pantalla.\n";

		_actualOption = 1;
		_maxOption = maxOption;
	}
	Screen::~Screen()
	{
		cout << "La pantalla ha sido eliminada de la memoria.\n";
	}


	// Funciones privadas.
	void Screen::changeOption(OPTION_DIRECTION optionDirection)
	{
		switch (optionDirection)
		{
		case OPTION_DIRECTION::PREVIOUS:
			_actualOption = (_actualOption == 1) ? _maxOption : --_actualOption; // Cambia a la opción anterior (la última si se está sobre la primera).
			break;

		case OPTION_DIRECTION::NEXT:
			_actualOption = (_actualOption == _maxOption) ? 1 : ++_actualOption; // Cambia a la opción siguiente (la primera si se está sobre la última).
			break;
		}

		cout << "Opcion actual: " << _actualOption << ".\n";
	}
}
