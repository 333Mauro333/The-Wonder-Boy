#include "animation.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Animation::Animation(Sprite target, ANIMATION_MODE animationMode)
	{
		this->animationMode = animationMode;
		this->target = target;
		actualFrame = 0;
		progress = 0.0f;

		cout << "Se ha creado una animacion.\n\n";
	}
	Animation::~Animation()
	{
		for (int i = 0; i < static_cast<int>(frameVector.size()); i++)
		{
			delete frameVector[i];
		}

		cout << "La animacion ha sido eliminada de la memoria.\n\n";
	}

	// Funciones p�blicas.
	void Animation::addFrame(Frame* frame)
	{
		frameVector.push_back(frame); // Agrega un frame al final del vector.
	}
	void Animation::update(float elapsed)
	{
		progress += elapsed;

		float p = progress;

		for (int i = 0; i < static_cast<int>(frameVector.size()); i++)
		{
			actualFrame = i;

			p -= frameVector[i]->getDuration();

			if (animationMode == ANIMATION_MODE::LOOP && p > 0.0f && i == static_cast<int>(frameVector.size()) - 1)
			{
				// Vuelve al comienzo de la iteraci�n (reiniciando la cuenta).
				i = -1; // "i" se convierte en -1 porque al llegar a "continue;", se inicia el for habiendo sumado 1 a "i".
				continue; // Vuelve al comienzo del loop, ignorando todo lo que est� despu�s de esta l�nea.
			}

			if (p <= 0.0f || i == static_cast<int>(frameVector.size()) - 1) // Si se lleg� al final del vector...
			{
				// Se queda congelado en el �ltimo frame.
				target.setTextureRect(frameVector[i]->getRect());
				break;
			}
		}
	}
	int Animation::getNumberOfFrame()
	{
		return actualFrame;
	}
	int Animation::getAmountOfFrames()
	{
		return static_cast<int>(frameVector.size());
	}
	void Animation::setDurationOfFrame(int ind, float newDuration)
	{
		frameVector[ind]->setDuration(newDuration);
	}
}
