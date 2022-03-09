#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include "frame/frame.h"

using std::vector;
using sf::Sprite;


enum class ANIMATION_MODE { ONCE, LOOP };

namespace the_wonder_boy
{
	class Animation
	{
	public:
		Animation(Sprite target, ANIMATION_MODE animationMode);
		~Animation();

		Sprite _target; // Este campo se declaró público porque al querer obtenerlo con un getter, se inhabilitan ciertas funcionalidades.

		void addFrame(Frame* frame);
		void update(float elapsed);

		int getNumberOfFrame();
		int getAmountOfFrames();
		void setDurationOfFrame(int ind, float newDuration);

		void resetAnimation();

	private:
		vector<Frame*> _frameVector;
		ANIMATION_MODE _animationMode;
		int _actualFrame;
		float _progress;
	};
}

#endif // !ANIMATION_H
