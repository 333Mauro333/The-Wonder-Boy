#ifndef LEVEL_H
#define LEVEL_H

#include "scenes/scene/scene.h"

#include "gameplay_elements/player/player.h"

using sf::View;


namespace the_wonder_boy
{
	class Level : public Scene
	{
	public:
		Level(RenderWindow* window);
		virtual ~Level();

	protected:
		View _view;

		void moveCameraInY(Player* player, float start, float end, float pixelsToMove, float deltaTime);

	private:
		virtual void updateCamera() = 0;

		virtual void resetLevel() = 0;
	};
}

#endif // !LEVEL_H
