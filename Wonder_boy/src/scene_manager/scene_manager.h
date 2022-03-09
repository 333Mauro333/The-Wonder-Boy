#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scenes/scene/scene.h"


namespace the_wonder_boy
{
	class SceneManager
	{
	public:
		static Scene* getActualScene();
		static void loadNewScene(Scene* newScene);

	private:
		static Scene* _scene;
	};
}

#endif // !SCENE_MANAGER_H
