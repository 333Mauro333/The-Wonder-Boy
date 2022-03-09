#ifndef FRAME_H
#define FRAME_H

#include "SFML/Graphics.hpp"

using sf::IntRect;


namespace the_wonder_boy
{
	class Frame
	{
	public:
		Frame(IntRect rect, float duration);
		~Frame();

		IntRect getRect();
		float getDuration();

		void setDuration(float duration);

	private:
		IntRect _rect;
		float _duration;
	};
}

#endif // !FRAME_H
