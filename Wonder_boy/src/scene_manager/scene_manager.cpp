#include "scene_manager.h"


namespace the_wonder_boy
{
	Scene* SceneManager::_scene;

	// Funciones p�blicas.
	Scene* SceneManager::getActualScene()
	{
		return _scene;
	}
	void SceneManager::loadNewScene(Scene* scene)
	{
		if (_scene != NULL)
		{
			delete _scene; // Se elimina la escena s�lo si hay una cargada.
		}

		_scene = scene;
	}
}
