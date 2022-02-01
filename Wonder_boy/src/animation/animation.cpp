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

	void Animation::addFrame() // Parámetro: clase Frame.
	{
		// Agrego a mi lista de frames.
	}
	void Animation::update(float elapsed)
	{
		progress += elapsed;

		float p = progress;

		// Hacer el for con tamaño de la lista de frames.
	}
	int Animation::getNumberOfFrame()
	{
		return actualFrame;
	}
}