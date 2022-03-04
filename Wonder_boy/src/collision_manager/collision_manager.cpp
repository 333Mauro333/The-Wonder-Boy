#include "collision_manager.h"


namespace the_wonder_boy
{
	bool CollisionManager::isColliding(Player* player, Floor* floor)
	{
		return player->isAlive() && player->getFallingSpeed() > -100.0f && player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getPosition().y > floor->getBoxCollision().getPosition().y &&
			player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getPosition().y - player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getSize().y < floor->getBoxCollision().getPosition().y + floor->getBoxCollision().getGlobalBounds().height &&
			player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getPosition().x + player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getSize().x / 2.0f > floor->getBoxCollision().getPosition().x - floor->getBoxCollision().getGlobalBounds().width / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getPosition().x - player->getBoxCollision(BOX_COLLISION_TYPE::FEET).getSize().x / 2.0f < floor->getBoxCollision().getPosition().x + floor->getBoxCollision().getGlobalBounds().width / 2.0f;
	}
	bool CollisionManager::isColliding(Player* player, Stone* stone)
	{
		return player->isAlive() && player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x + player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().width / 2.0f > stone->getBoxCollision().getPosition().x - stone->getBoxCollision().getGlobalBounds().width / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().width / 2.0f < stone->getBoxCollision().getPosition().x + stone->getBoxCollision().getGlobalBounds().width / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().y > stone->getBoxCollision().getPosition().y - stone->getBoxCollision().getGlobalBounds().height &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().y - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().height < stone->getBoxCollision().getPosition().y;
	}
	bool CollisionManager::isColliding(Player* player, Bonfire* bonfire)
	{
		return player->isAlive() && player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x + player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().width / 2.0f > bonfire->getBoxCollision().getPosition().x - bonfire->getBoxCollision().getGlobalBounds().width / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().width / 2.0f < bonfire->getBoxCollision().getPosition().x + bonfire->getBoxCollision().getGlobalBounds().width / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().y > bonfire->getBoxCollision().getPosition().y - bonfire->getBoxCollision().getGlobalBounds().height &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().y - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().height < bonfire->getBoxCollision().getPosition().y;
	}
	bool CollisionManager::isColliding(Player* player, Enemy* enemy)
	{
		return enemy->isActive() && !enemy->isDefeated() && player->isAlive() &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x + player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().width / 2.0f > enemy->getBoxCollision().getPosition().x - enemy->getBoxCollision().getGlobalBounds().width / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().width / 2.0f < enemy->getBoxCollision().getPosition().x + enemy->getBoxCollision().getGlobalBounds().width / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().y > enemy->getBoxCollision().getPosition().y - enemy->getBoxCollision().getGlobalBounds().height &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().y - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().height < enemy->getBoxCollision().getPosition().y;
	}
	bool CollisionManager::isColliding(Player* player, Fruit* fruit)
	{
		return fruit->isActive() && player->isAlive() &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x + player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().width / 2.0f > fruit->getBoxCollision().getPosition().x - fruit->getBoxCollision().getGlobalBounds().width / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().x - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().width / 2.0f < fruit->getBoxCollision().getPosition().x + fruit->getBoxCollision().getGlobalBounds().width / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().y > fruit->getBoxCollision().getPosition().y - fruit->getBoxCollision().getGlobalBounds().height / 2.0f &&
			player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getPosition().y - player->getBoxCollision(BOX_COLLISION_TYPE::ENTIRE).getGlobalBounds().height < fruit->getBoxCollision().getPosition().y + fruit->getBoxCollision().getGlobalBounds().height / 2.0f;
	}

	bool CollisionManager::isColliding(StoneHammer* stoneHammer, Floor* floor)
	{
		return stoneHammer->getIsThrown() &&
			stoneHammer->getBoxCollision().getPosition().y + stoneHammer->getBoxCollision().getGlobalBounds().height / 2.0f > floor->getBoxCollision().getPosition().y &&
			stoneHammer->getBoxCollision().getPosition().y - stoneHammer->getBoxCollision().getGlobalBounds().height / 2.0f < floor->getBoxCollision().getPosition().y + floor->getBoxCollision().getGlobalBounds().height &&
			stoneHammer->getBoxCollision().getPosition().x + stoneHammer->getBoxCollision().getGlobalBounds().width / 2.0f > floor->getBoxCollision().getPosition().x - floor->getBoxCollision().getGlobalBounds().width / 2.0f &&
			stoneHammer->getBoxCollision().getPosition().x - stoneHammer->getBoxCollision().getGlobalBounds().width / 2.0f < floor->getBoxCollision().getPosition().x + floor->getBoxCollision().getGlobalBounds().width / 2.0f;
	}
	bool CollisionManager::isColliding(StoneHammer* stoneHammer, Enemy* enemy)
	{
		return stoneHammer->getIsThrown() && !enemy->isDefeated() && enemy->isActive() &&
			stoneHammer->getBoxCollision().getPosition().y + stoneHammer->getBoxCollision().getGlobalBounds().height / 2.0f > enemy->getBoxCollision().getPosition().y - enemy->getBoxCollision().getGlobalBounds().height &&
			stoneHammer->getBoxCollision().getPosition().y - stoneHammer->getBoxCollision().getGlobalBounds().height / 2.0f < enemy->getBoxCollision().getPosition().y &&
			stoneHammer->getBoxCollision().getPosition().x + stoneHammer->getBoxCollision().getGlobalBounds().width / 2.0f > enemy->getBoxCollision().getPosition().x - enemy->getBoxCollision().getGlobalBounds().width / 2.0f &&
			stoneHammer->getBoxCollision().getPosition().x - stoneHammer->getBoxCollision().getGlobalBounds().width / 2.0f < enemy->getBoxCollision().getPosition().x + enemy->getBoxCollision().getGlobalBounds().width / 2.0f;
	}
}
