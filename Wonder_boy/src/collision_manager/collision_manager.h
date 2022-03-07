#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "player/player.h"
#include "floor/floor.h"
#include "platform/platform.h"
#include "stone_hammer/stone_hammer.h"
#include "obstacles/stone/stone.h"
#include "obstacles/bonfire/bonfire.h"
#include "enemies/enemy/enemy.h"
#include "items/fruit/fruit.h"


namespace the_wonder_boy
{
	class CollisionManager
	{
	public:
		static bool isColliding(Player* player, Floor* floor);
		static bool isColliding(Player* player, Platform* platform);
		static bool isColliding(Player* player, Stone* stone);
		static bool isColliding(Player* player, Bonfire* stone);
		static bool isColliding(Player* player, Enemy* enemy);
		static bool isColliding(Player* player, Fruit* fruit);
		static bool isColliding(Player* player, Sprite hammer);

		static bool isColliding(StoneHammer* stoneHammer, Floor* floor);
		static bool isColliding(StoneHammer* stoneHammer, Enemy* enemy);
	};
}

#endif // !COLLISION_MANAGER_H
