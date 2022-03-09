#include "frame.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Frame::Frame(IntRect rect, float duration)
	{
		_rect = rect;
		_duration = duration;

		cout << "Se ha creado un frame.\n\n";
	}
	Frame::~Frame()
	{
		cout << "El frame ha sido eliminado de la memoria.\n";
	}

	// Funciones públicas.
	IntRect Frame::getRect()
	{
		return _rect;
	}
	float Frame::getDuration()
	{
		return _duration;
	}

	void Frame::setDuration(float duration)
	{
		_duration = duration;
	}
}
