#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include "frame/frame.h"

using sf::Sprite;
using std::vector;


enum class ANIMATION_MODE { ONCE, LOOP };

namespace the_wonder_boy
{
	class Animation
	{
	public:
		Animation(Sprite& target, ANIMATION_MODE animationMode);
		~Animation();

		void addFrame(Frame frame);
		void update(float elapsed);
		int getNumberOfFrame();

	private:
		vector<Frame> frameVector;
		ANIMATION_MODE animationMode;
		Sprite target;
		int actualFrame;
		float progress;
	};
}

#endif // !ANIMATION_H
