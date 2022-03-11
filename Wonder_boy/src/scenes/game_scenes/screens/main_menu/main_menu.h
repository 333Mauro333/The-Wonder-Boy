#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "scenes/screen/screen.h"

#include "button/Button.h"

using sf::RectangleShape;
using sf::Font;
using sf::Text;


enum class SELECTED_OPTION { PLAY = 1, CREDITS, QUIT };

namespace the_wonder_boy
{
	class MainMenu : public Screen
	{
	public:
		MainMenu(RenderWindow* window, SELECTED_OPTION selectedOption);
		~MainMenu();

		void update() override;
		void draw() override;
		void checkKeyPressedOnce(Keyboard::Key key) override;
		void checkKeyReleased(Keyboard::Key key) override;

	private:
		Font font;
		Text gameTitle;
		bool toBlack;

		RectangleShape background; // Rectángulo para pintar el fondo.

		static const int buttonsSize = 3;
		Button* buttons[buttonsSize];
		string optionsList[buttonsSize]; // Lista de nombres para las opciones para facilitar la asignación de los botones en el init.

		void init() override;
		void destroy() override;

		void updateTextColor();
	};
}

#endif // !MAIN_MENU_H
