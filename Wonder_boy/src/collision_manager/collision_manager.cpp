#include "collision_manager.h"


namespace the_wonder_boy
{
	bool CollisionManager::isColliding(Player* player, Floor* floor)
	{
		return player->getFallingSpeed() > -100.0f && player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getPosition().y > floor->getBoxCollision().getPosition().y &&
			player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getPosition().y - player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getSize().y < floor->getBoxCollision().getPosition().y + floor->getBoxCollision().getGlobalBounds().height &&
			player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getPosition().x + player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getSize().x / 2.0f > floor->getBoxCollision().getPosition().x - floor->getBoxCollision().getGlobalBounds().width / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getPosition().x - player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getSize().x / 2.0f < floor->getBoxCollision().getPosition().x + floor->getBoxCollision().getGlobalBounds().width / 2.0f;
	}
<<<<<<< HEAD
	bool CollisionManager::isColliding(Player* player, Stone* stone)
	{
		return player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x + player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().width / 2.0f > stone->getBoxCollision().getPosition().x - stone->getBoxCollision().getGlobalBounds().width / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().width / 2.0f < stone->getBoxCollision().getPosition().x + stone->getBoxCollision().getGlobalBounds().width / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().y > stone->getBoxCollision().getPosition().y - stone->getBoxCollision().getGlobalBounds().height &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().y - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().height < stone->getBoxCollision().getPosition().y;
	}
=======
>>>>>>> c5c1d9d70f7c3cc163452bd42d4dcf9ec9da79da

	bool CollisionManager::isColliding(StoneHammer* stoneHammer, Floor* floor)
	{
		return stoneHammer->getIsThrown() &&
			stoneHammer->getBoxCollision().getPosition().y + stoneHammer->getBoxCollision().getGlobalBounds().height / 2.0f > floor->getBoxCollision().getPosition().y &&
			stoneHammer->getBoxCollision().getPosition().y - stoneHammer->getBoxCollision().getGlobalBounds().height / 2.0f < floor->getBoxCollision().getPosition().y + floor->getBoxCollision().getGlobalBounds().height &&
			stoneHammer->getBoxCollision().getPosition().x + stoneHammer->getBoxCollision().getGlobalBounds().width / 2.0f > floor->getBoxCollision().getPosition().x - floor->getBoxCollision().getGlobalBounds().width / 2.0f &&
			stoneHammer->getBoxCollision().getPosition().x - stoneHammer->getBoxCollision().getGlobalBounds().width / 2.0f < floor->getBoxCollision().getPosition().x + floor->getBoxCollision().getGlobalBounds().width / 2.0f;
	}
}