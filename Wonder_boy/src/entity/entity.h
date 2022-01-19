#ifndef ENTITY_H
#define ENTITY_H


struct Vector2f
{
	float x;
	float y;
};

namespace the_wonder_boy
{
	class Entity
	{
	public:
		Entity(float x, float y);
		~Entity();

		Vector2f getPosition();

	private:
		Vector2f position;
	};
}

#endif // !ENTITY_H
