#ifndef SCENE_H
#define SCENE_H

#include "SFML/Graphics.hpp"

using sf::RenderWindow;
using sf::Keyboard;


namespace the_wonder_boy
{
	class Scene
	{
	public:
		Scene(RenderWindow* window);
		virtual ~Scene();

		virtual void update() = 0;
		virtual void draw() = 0;
		virtual void checkKeyPressedOnce(Keyboard::Key key) = 0;
		virtual void checkKeyReleased(Keyboard::Key key) = 0;

	protected:
		RenderWindow* window;

	private:
		virtual void init() = 0;
		virtual void destroy() = 0;
	};
}

#endif // !SCENE_H
