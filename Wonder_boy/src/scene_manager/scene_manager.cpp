#include "scene_manager.h"

namespace the_wonder_boy
{
	Scene* SceneManager::scene;

	Scene* SceneManager::getActualScene()
	{
		return scene;
	}
	void SceneManager::loadNewScene(Scene* newScene)
	{
		if (scene != NULL)
		{
			scene->destroy();
		}

		scene = newScene;
	}
}