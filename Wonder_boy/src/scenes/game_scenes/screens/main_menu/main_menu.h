#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "scenes/scene/scene.h"

#include "button/Button.h"

using sf::RectangleShape;
using sf::Font;
using sf::Text;


enum class SELECTED_OPTION { PLAY = 1, CREDITS, QUIT };
enum class OPTION_DIRECTION { PREVIOUS, NEXT };

namespace the_wonder_boy
{
	class MainMenu : public Scene
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

		int option; // Número de opción actual, la cual va a definir sobre qué opción estoy parado.

		void init() override;
		void destroy() override;

		void changeOption(OPTION_DIRECTION optionDirection);

		void updateTextColor();
	};
}

#endif // !MAIN_MENU_H
