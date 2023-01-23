#include "EnemyEntity.hpp"

EnemyEntity::EnemyEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder)
	: WorldSpaceEntity(x, y, scale, tex, sortOrder)
{
	velocity = Vector2(0, 0);
	currAnimState = Assets::Instance().img_EnemyWalkRight;
}

void EnemyEntity::update()
{
	updatePosition();
	updateCollision();
	updateAnimation();
	WorldSpaceEntity::update();
}

void EnemyEntity::updatePosition()
{
	if (Game::Instance().player->pos->x > pos->x)
	{
		facingRight = true;
		velocity.x = walkSpeed;
	}
	else if (Game::Instance().player->pos->x < pos->x)
	{
		facingRight = false;
		velocity.x = -walkSpeed;
	}
	else
	{
		velocity.x = 0;
	}
	*pos += velocity;
}

void EnemyEntity::updateCollision()
{
	if (pos->x > 1600)
		pos->x = 1600;
	if (pos->x < -1600)
		pos->x = -1600;
}

void EnemyEntity::updateAnimation()
{
	static Uint32 lastUpdate = 0;
	if (abs(velocity.x) > .01f)
	{
		Uint32 current = SDL_GetTicks();
		if (facingRight)
			currAnimState = Assets::Instance().img_EnemyWalkRight;
		else
			currAnimState = Assets::Instance().img_EnemyWalkLeft;
		float dT = (current - lastUpdate) / 1000.0f;
		int framesToUpdate = floor(dT / (1.0f / animatedFPS));
		if (framesToUpdate > 0) {
			currAnimIdx += framesToUpdate;
			//todo make anim states vectors
			currAnimIdx %= 8;
			lastUpdate = current;
		}
		tex = currAnimState[currAnimIdx];

	}
	else
	{
		currAnimIdx = 0;
		if (facingRight)
			tex = Assets::Instance().img_EnemyWalkRight[0];
		else
			tex = Assets::Instance().img_EnemyWalkLeft[0];
	}
}
