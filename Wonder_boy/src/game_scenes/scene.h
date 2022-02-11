#ifndef SCENE_H
#define SCENE_H

#include "SFML/Graphics.hpp"

using sf::RenderWindow;


namespace the_wonder_boy
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void update(float deltaTime) = 0;
		virtual void draw() = 0;

	protected:
		RenderWindow* window;

	private:
		virtual void init() = 0;
		virtual void destroy() = 0;
	};
}

#endif // !SCENE_H
