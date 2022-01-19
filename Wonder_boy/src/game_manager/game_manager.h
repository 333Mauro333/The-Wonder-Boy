#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

using sf::RenderWindow;


namespace the_wonder_boy
{
	class GameManager
	{
	public:
		RenderWindow* window;

		GameManager(unsigned int width, unsigned int height, const std::string windowTitle);
		~GameManager();

		void run();

	private:
		void init();
		void update(float deltaTime);
		void draw();
		void destroy();

		void checkEvents();
	};
}

#endif // !GAME_MANAGER_H
