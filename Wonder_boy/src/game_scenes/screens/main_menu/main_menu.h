#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "game_scenes/scene.h"

using sf::RectangleShape;


namespace the_wonder_boy
{
	class MainMenu : public Scene
	{
	public:
		MainMenu(RenderWindow* window);
		~MainMenu();

		void update(float deltaTime) override;
		void draw() override;
		void checkKeyPressedOnce(Keyboard::Key key) override;
		void checkKeyReleased(Keyboard::Key key) override;

	private:
		RectangleShape background;

		static const int buttonsSize = 4;
		RectangleShape buttons[buttonsSize];

		void init() override;
		void destroy() override;
	};

}

#endif // !MAIN_MENU_H
