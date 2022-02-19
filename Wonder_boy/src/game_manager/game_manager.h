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

		static float getDeltaTime();

	private:
		static Vector2u windowSize;
		static float deltaTime;
		int fps;
		
		void init();
		void update();
		void draw();
		void destroy();

		void checkEvents();

		void limitFrames();
	};
}

#endif // !GAME_MANAGER_H
