#include "scene_manager.h"

namespace the_wonder_boy
{
	Scene* SceneManager::getActualScene()
	{
		return scene;
	}
	void SceneManager::loadNewScene(Scene* newScene)
	{
		scene = newScene;
	}
}