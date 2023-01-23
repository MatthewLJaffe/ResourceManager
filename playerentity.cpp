#include "PlayerEntity.hpp"

PlayerEntity::PlayerEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder, float width, float height)
	: WorldSpaceEntity(x, y, scale, tex, sortOrder)
{
	currAnimState = Assets::Instance().img_PlayerWalkRight;
	velocity = Vector2(0, 0);
	this->width = width;
	this->height = height;
}

void PlayerEntity::update()
{
	updatePosition();
	updateCollision();
	updateAnimation();
	WorldSpaceEntity::update();
}

void PlayerEntity::updatePosition()
{
	if (InputManager::Instance().getADown())
	{
		facingRight = false;
		velocity.x = -walkSpeed;
	}
	else if (InputManager::Instance().getDDown())
	{
		facingRight = true;
		velocity.x = walkSpeed;
	}
	else
	{
		velocity.x = 0;
	}
	*pos += velocity;
}

void PlayerEntity::updateCollision()
{
	if (pos->x > 1600)
		pos->x = 1600;
	if (pos->x < -1600)
		pos->x = -1600;
}

bool PlayerEntity::posInView(Vector2 pos)
{
	return abs(this->pos->x - pos.x) <= 160;
}


void PlayerEntity::updateAnimation()
{
	static Uint32 lastUpdate = 0;
	if (abs(velocity.x) > .01f)
	{
		Uint32 current = SDL_GetTicks();
		if (facingRight)
			currAnimState = Assets::Instance().img_PlayerWalkRight;
		else
			currAnimState = Assets::Instance().img_PlayerWalkLeft;
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
			tex = Assets::Instance().img_PlayerRight;
		else
			tex = Assets::Instance().img_PlayerLeft;
	}
}