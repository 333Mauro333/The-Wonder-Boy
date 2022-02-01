#include "animation.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Animation::Animation(Sprite& target, ANIMATION_MODE animationMode)
	{
		this->animationMode = animationMode;
		this->target = target;
		actualFrame = 0;
		progress = 0.0f;

		cout << "Se ha creado una animacion.\n\n";
	}
	Animation::~Animation()
	{
		cout << "La animacion ha sido eliminada de la memoria.\n\n";
	}

	void Animation::addFrame(Frame frame)
	{
		frameVector.push_back(frame); // Lo agrega al final.
	}
	void Animation::update(float elapsed)
	{
		progress += elapsed;

		float p = progress;

		for (int i = 0; i < frameVector.size(); i++)
		{
			actualFrame = i;

			p -= frameVector[i].getDuration();

			if (animationMode == ANIMATION_MODE::LOOP && p > 0.0f && i == frameVector.size() - 1)
			{
				// Vuelve al comienzo de la iteración (reiniciando la cuenta).
				i = 0;
				continue;
			}

			if (p <= 0.0f || i == frameVector.size() - 1)
			{
				// Deja el último frame, sin repetir.
				target.setTextureRect(frameVector[i].getRect());
				break;
			}
		}

	}
	int Animation::getNumberOfFrame()
	{
		return actualFrame;
	}
}
