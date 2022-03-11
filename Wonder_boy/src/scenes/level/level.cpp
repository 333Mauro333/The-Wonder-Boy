#include "level.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Level::Level(RenderWindow* window) : Scene(window)
	{
		cout << "Se ha creado un nivel.\n";
	}
	Level::~Level()
	{
		cout << "El nivel ha sido eliminado de la memoria.\n";
	}


	// Funciones privadas.
	void Level::moveCameraInY(Player* player, float start, float end, float pixelsToMove, float deltaTime)
	{
		if (player->getPosition().x >= start && player->getPosition().x <= end)
		{
			const float distanceTrayectory = end - start; // Distancia total de principio a fin.

			// Movimiento total / distancia entre la que se va a mover * velocidad del jugador en cada frame.
			_view.setCenter(_view.getCenter().x, _view.getCenter().y + pixelsToMove / distanceTrayectory * player->getSpeed() * deltaTime);
			_window->setView(_view);
		}
	}
}
