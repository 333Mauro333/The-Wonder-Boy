#ifndef CURTAIN_MANAGER_H
#define CURTAIN_MANAGER_H

#include "SFML/Graphics.hpp"

#include "scene_manager/scene_manager.h"

using sf::RenderWindow;
using sf::RectangleShape;
using sf::Vector2f;
using sf::Vector2u;


enum class CURTAIN_TYPE { FADE, LEFT_TO_RIGHT };

namespace the_wonder_boy
{
	class CurtainManager
	{
	public:
		static void initValues(Vector2u curtainSize);
		static void update(float deltaTime);
		static void draw(RenderWindow* window);

		static void startToCover(CURTAIN_TYPE curtainType);
		static void startToShow(CURTAIN_TYPE curtainType);

		static void setCurtainPosition(Vector2f position);

		static bool isActive();
		static bool screenIsBlack();

	private:
		static CURTAIN_TYPE wayToHide;
		static CURTAIN_TYPE wayToShow;

		static bool fadingOut;
		static bool fadingIn;

		static RectangleShape curtain;

		static float timeToFinishCurtainAction;
		static const float maxUint8Value;

		static void show(float deltaTime);
		static void cover(float deltaTime);
	};
}

#endif // !CURTAIN_MANAGER_H
