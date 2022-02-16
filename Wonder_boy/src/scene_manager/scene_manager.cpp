#include "scene_manager.h"


namespace the_wonder_boy
{
	Scene* SceneManager::scene;

	// Funciones p�blicas.
	Scene* SceneManager::getActualScene()
	{
		return scene;
	}
	void SceneManager::loadNewScene(Scene* newScene)
	{
		if (scene != NULL)
		{
			delete scene; // Se elimina la escena s�lo si hay una cargada.
		}

		scene = newScene;
	}
}
