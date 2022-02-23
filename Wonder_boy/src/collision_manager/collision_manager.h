#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "player/player.h"
#include "floor/floor.h"


namespace the_wonder_boy
{
	class CollisionManager
	{
	public:
		static bool isColliding(Player* player, Floor* floor);

	private:

	};
}

#endif // !COLLISION_MANAGER_H
