#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "game_scenes/scene.h"


namespace the_wonder_boy
{
	class SceneManager
	{
	public:
		static Scene* getActualScene();
		static void loadNewScene(Scene* newScene);

	private:
		static Scene* scene;
	};
}

#endif // !SCENE_MANAGER_H
