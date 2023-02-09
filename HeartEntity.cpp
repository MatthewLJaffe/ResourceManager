
#include "HeartEntity.hpp"

HeartEntity::HeartEntity(float x, float y, float healthAmount, HealthSpawner* spawner)
	: WorldSpaceEntity(x, y, 4, Assets::Instance().img_Heart, 4)
{
	this->healthAmount = healthAmount;
	this->width = 14;
	this->height = 12;
	this->spawner = spawner;
}


void HeartEntity::update()
{
	WorldSpaceEntity::update();
	PlayerEntity* player = Game::Instance().GetMainGameState()->player;
	if (utils::boxCollision(this->pos.x, this->pos.y, this->width, this->height, player->pos.x, player->pos.y, player->width, player->height))
	{
		player->addHealth(healthAmount);
		spawner->currHealth--;
		Game::Instance().RemoveAndDeleteEntity(this);
	}
}
