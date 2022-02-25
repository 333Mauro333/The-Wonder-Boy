#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "player/player.h"
#include "floor/floor.h"
#include "stone_hammer/stone_hammer.h"
#include "obstacles/stone/stone.h"
#include "obstacles/bonfire/bonfire.h"


namespace the_wonder_boy
{
	class CollisionManager
	{
	public:
		static bool isColliding(Player* player, Floor* floor);
		static bool isColliding(Player* player, Stone* stone);
		static bool isColliding(Player* player, Bonfire* stone);

		static bool isColliding(StoneHammer* stoneHammer, Floor* floor);

	private:

	};
}

#endif // !COLLISION_MANAGER_H
