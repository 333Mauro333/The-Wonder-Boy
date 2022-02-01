#include "frame.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Frame::Frame(IntRect rect, float duration)
	{
		this->rect = rect;
		this->duration = duration;

		cout << "Se ha creado un frame.\n\n";
	}
	Frame::~Frame()
	{
		cout << "El frame ha sido eliminado de la memoria.\n";
	}

	IntRect Frame::getRect()
	{
		return rect;
	}
	float Frame::getDuration()
	{
		return duration;
	}
}
