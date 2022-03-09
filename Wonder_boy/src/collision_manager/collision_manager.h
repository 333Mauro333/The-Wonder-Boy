#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "gameplay_elements/player/player.h"
#include "gameplay_elements/floor/floor.h"
#include "gameplay_elements/platform/platform.h"
#include "gameplay_elements/stone_hammer/stone_hammer.h"
#include "gameplay_elements/obstacles/stone/stone.h"
#include "gameplay_elements/obstacles/bonfire/bonfire.h"
#include "gameplay_elements/enemies/enemy/enemy.h"
#include "gameplay_elements/items/fruit/fruit.h"


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
