#ifndef SCENE_H
#define SCENE_H

namespace the_wonder_boy
{
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void init() = 0;
		virtual void update(float deltaTime) = 0;
		virtual void draw() = 0;
		virtual void destroy() = 0;
	};
}

#endif // !SCENE_H
