#include "BombEntity.hpp"

BombEntity::BombEntity(float x, float y, float width, float height, int sortOrder, float damage)
	: WorldSpaceEntity(x, y, 4, Assets::Instance().imgs_bomb[0], sortOrder)
{
	this->damage = damage;
	this->startDelay = .75;
	this->damageStartFrame = 11;
	this->damageEndFrame = 15;
	this->width = width;
	this->height = height;
	explodeAnim = Assets::Instance().imgs_bomb;
	lastUpdateTime = Game::Instance().GetGameTime();
	exploding = false;
	animating = false;
	currAnimFrameTime = 0;
	currAnimIdx = 0;
}

void BombEntity::update()
{
	Uint32 current = Game::Instance().GetGameTime();
	float dT = (current - lastUpdateTime) / 1000.0f;
	startDelay -= dT;
	WorldSpaceEntity::update();
	if (startDelay <= 0 && !animating)
	{
		animating = true;
	}
	if (exploding)
		updateCollision();
	if (animating)
		updateAnimation(dT);
	lastUpdateTime = current;
}

void BombEntity::updateAnimation(float dT)
{
	currAnimFrameTime += dT;
	int framesToUpdate = floor(currAnimFrameTime / (1.0f / animationFPS));
	if (framesToUpdate > 0)
	{
		currAnimIdx += framesToUpdate;
		if (currAnimIdx >= damageStartFrame && !exploding)
		{
			exploding = true;
		}
		else if (exploding && currAnimIdx >= damageEndFrame)
		{
			exploding = false;
		}
		if (currAnimIdx >= explodeAnim.size())
		{
			Game::Instance().RemoveAndDeleteEntity(this);
			return;
		}
		currAnimFrameTime = 0;
		tex = explodeAnim[currAnimIdx];
	}
}

void BombEntity::updateCollision()
{
	std::vector<EnemyEntity*> enemies = Game::Instance().GetMainGameState()->enemies;
	for (int i = 0; i < enemies.size(); i++)
	{
		if (utils::boxCollision(enemies[i]->pos->x, enemies[i]->pos->y, enemies[i]->width, enemies[i]->height, this->pos->x, this->pos->y, width, height))
			enemies[i]->takeDamage(damage);
	}
}