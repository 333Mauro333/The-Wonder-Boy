#include "scene.h"

#include <iostream>

using std::cout;


namespace the_wonder_boy
{
	Scene::Scene(RenderWindow* window)
	{
		this->window = window;

		cout << "Se ha creado una escena.\n";
	}
	Scene::~Scene()
	{
		cout << "La escena ha sido eliminada de la memoria.\n\n";
	}
}
