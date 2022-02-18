#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>

#include "SFML/Graphics.hpp"

#include "entity/entity.h"

using std::string;
using sf::RectangleShape;
using sf::Texture;
using sf::Sprite;
using sf::RenderWindow;
using sf::Font;
using sf::Text;


namespace the_wonder_boy
{
	class Button : public Entity
	{
	public:
		Button(float x, float y, float w, float h, string optionName);
		~Button();

		void update(float deltaTime);
		void draw(RenderWindow* window);

		void setSelected(bool isSelected);

	private:
		Texture texButton;
		Sprite sprButton;
		Font font;
		Text text;

		bool isSelected; // Define si el botón está seleccionado o no.

		// Probar el cambio de tamaño de los botones para remarcar la opcion seleccionada.
	};
}

#endif // !BUTTON_H
