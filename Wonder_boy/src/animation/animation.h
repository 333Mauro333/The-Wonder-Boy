#ifndef ANIMATION_H
#define ANIMATION_H

#include "SFML/Graphics.hpp"

#include <list>

using sf::Sprite;
using std::list;


enum class ANIMATION_MODE { ONCE, LOOP };

namespace the_wonder_boy
{
	class Animation
	{
	public:
		Animation(Sprite& target, ANIMATION_MODE animationMode);
		~Animation();

		void addFrame();
		void update(float elapsed);
		int getNumberOfFrame();

	private:
		ANIMATION_MODE animationMode;
		Sprite target;
		int actualFrame;
		float progress;
	};
}

#endif // !ANIMATION_H
