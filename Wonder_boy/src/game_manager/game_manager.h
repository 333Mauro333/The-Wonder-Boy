#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

using sf::RenderWindow;
using sf::Vector2u;


namespace the_wonder_boy
{
	class GameManager
	{
	public:
		RenderWindow* window;

		GameManager(unsigned int width, unsigned int height, const std::string windowTitle);
		~GameManager();

		void run();

		static Vector2u getWindowSize();
		static void setWindowSize(int width, int height);

	private:
		static Vector2u windowSize;
		// Agregar función de deltaTime 1000/frames en un sleep.
		void init();
		void update(float deltaTime);
		void draw();
		void destroy();

		void checkEvents();
	};
}

#endif // !GAME_MANAGER_H
