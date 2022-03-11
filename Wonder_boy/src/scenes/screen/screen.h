#ifndef SCREEN_H
#define SCREEN_H

#include "scenes/scene/scene.h"


enum class OPTION_DIRECTION { PREVIOUS, NEXT };

namespace the_wonder_boy
{
	class Screen : public Scene
	{
	public:
		Screen(RenderWindow* window, int maxOption);
		virtual ~Screen();

	protected:
		int _actualOption;

		void changeOption(OPTION_DIRECTION optionDirection);

	private:
		int _maxOption;
	};
}

#endif // !SCREEN_H
