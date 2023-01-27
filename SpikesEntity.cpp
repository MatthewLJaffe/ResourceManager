#include "SpikesEntity.hpp"

SpikesEntity::SpikesEntity(float x, float y, float width, float height, int sortOrder, float damage, int damageTicks)
	: WorldSpaceEntity(x, y, 4, Assets::Instance().img_ScrapPile, sortOrder)
{
	this->width = width;
	this->height = height;
	this->damage = damage;
	this->damageTicks = damageTicks;
}

void SpikesEntity::update()
{
	std::vector<EnemyEntity*> enemies = Game::Instance().GetMainGameState()->enemies;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (utils::boxCollision(this->pos->x, this->pos->y, width, height, enemies[i]->pos->x, enemies[i]->pos->y, enemies[i]->width, enemies[i]->height))
		{
			if (enemies[i]->takeSpikeDamage(damage))
			{
				this->damageTicks--;
				if (damageTicks <= 0)
				{
					destroySpikes();
					return;
				}
			}
		}
	}
	WorldSpaceEntity::update();
}

void SpikesEntity::destroySpikes()
{
	Game::Instance().RemoveAndDeleteEntity(this);
}