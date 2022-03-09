#include "animation.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Animation::Animation(Sprite target, ANIMATION_MODE animationMode)
	{
		_animationMode = animationMode;
		_target = target;
		_actualFrame = 0;
		_progress = 0.0f;

		cout << "Se ha creado una animacion.\n\n";
	}
	Animation::~Animation()
	{
		for (int i = 0; i < static_cast<int>(_frameVector.size()); i++)
		{
			delete _frameVector[i];
		}

		cout << "La animacion ha sido eliminada de la memoria.\n\n";
	}


	// Funciones públicas.
	void Animation::addFrame(Frame* frame)
	{
		_frameVector.push_back(frame); // Agrega un frame al final del vector.
	}
	void Animation::update(float elapsed)
	{
		_progress += elapsed;

		float p = _progress;

		for (int i = 0; i < static_cast<int>(_frameVector.size()); i++)
		{
			_actualFrame = i;

			p -= _frameVector[i]->getDuration();

			if (_animationMode == ANIMATION_MODE::LOOP && p > 0.0f && i == static_cast<int>(_frameVector.size()) - 1)
			{
				// Vuelve al comienzo de la iteración (reiniciando la cuenta).
				i = -1; // "i" se convierte en -1 porque al llegar a "continue;", se inicia el for habiendo sumado 1 a "i".
				continue; // Vuelve al comienzo del loop, ignorando todo lo que está después de esta línea.
			}

			if (p <= 0.0f || i == static_cast<int>(_frameVector.size()) - 1) // Si se llegó al final del vector...
			{
				// Se queda congelado en el último frame.
				_target.setTextureRect(_frameVector[i]->getRect());
				break;
			}
		}
	}

	int Animation::getNumberOfFrame()
	{
		return _actualFrame;
	}
	int Animation::getAmountOfFrames()
	{
		return static_cast<int>(_frameVector.size());
	}
	void Animation::setDurationOfFrame(int ind, float newDuration)
	{
		_frameVector[ind]->setDuration(newDuration);
	}

	void Animation::resetAnimation()
	{
		_actualFrame = 0;
		_progress = 0.0f;
	}
}
