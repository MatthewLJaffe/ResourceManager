#include "BulletEntity.hpp"

BulletEntity::BulletEntity(float x, float y, SDL_Texture* tex, int sortOrder, float damage, float speed,
	float travelTime, Vector2 size, Vector2 explosionSize, bool facingRight, std::vector<SDL_Texture*> rightAnimation, std::vector<SDL_Texture*> leftAnimation, int enemiesDamageable)
	:WorldSpaceEntity (x, y, 4, tex, sortOrder)
{
	this->damage = damage;
	this->speed = speed;
	this->travelTime = travelTime;
	this->size = size;
	this->explosionSize = explosionSize;
	this->currAnimIndex = 0;
	this->enemiesDamageable = enemiesDamageable;
	lastPosUpdate = Game::Instance().GetGameTime();
	startTime = lastPosUpdate;
	if (facingRight)
	{
		this->destroyAnimation = rightAnimation;
		this->velocity = Vector2(speed, 0);
	}
	else
	{
		this->destroyAnimation = leftAnimation;
		this->velocity = Vector2(-speed, 0);
	}
}

void BulletEntity::update()
{
	WorldSpaceEntity::update();
	if (!destroy)
	{
		Uint32 current = Game::Instance().GetGameTime();
		float currTravelTime = (current - startTime) / 1000.0f;
		if (currTravelTime > travelTime)
		{
			destroy = true;
			lastAnimUpdate = Game::Instance().GetGameTime();
		}
		updatePosition();
	}
	updateCollision();
	updateAnimation();
}

void BulletEntity::updatePosition()
{
	Uint32 current = Game::Instance().GetGameTime();
	float dT = (current - lastPosUpdate) / 1000.0f;
	this->pos += velocity * dT;
	lastPosUpdate = current;
}

void BulletEntity::updateCollision()
{
	if (enemiesDamageable <= 0) return;
	std::vector<EnemyEntity*> enemyList = Game::Instance().GetMainGameState()->enemies;
	Vector2 hitboxSize = this->size;
	if (destroy)
		hitboxSize = this->explosionSize;
	for (size_t i = 0; i < enemyList.size(); i++)
	{
		if (utils::boxCollision(pos.x, pos.y, hitboxSize.x, hitboxSize.y, enemyList[i]->pos.x, enemyList[i]->pos.y, enemyList[i]->width, enemyList[i]->height))
		{
			enemyList[i]->takeDamage(damage);
			enemiesDamageable--;
			if (!destroy)
			{
				lastAnimUpdate = Game::Instance().GetGameTime();
				destroy = true;
			}
			if (enemiesDamageable <= 0)
				break;
		}
	}
}

void BulletEntity::updateAnimation()
{
	if (!destroy) return;
	Uint32 current = Game::Instance().GetGameTime();
	float dT = (current - lastAnimUpdate) / 1000.0f;
	int framesToUpdate = static_cast<int>(floor(dT / (1.0f / animatedFPS)));
	if (framesToUpdate > 0) {
		currAnimIndex += framesToUpdate;
		if (currAnimIndex >= destroyAnimation.size())
		{
			Game::Instance().RemoveAndDeleteEntity(this);
		}
		else
		{
			tex = destroyAnimation[currAnimIndex];
		}
		lastAnimUpdate = current;

	}
}
