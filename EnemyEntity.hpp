#pragma once
#include "WorldSpaceEntity.hpp"
#include "Assets.hpp"
#include "Game.hpp"

class EnemyEntity : public WorldSpaceEntity
{
public:
	EnemyEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder);
	float walkSpeed = .25f;
	Vector2 velocity;
	int currAnimIdx = 0;
	SDL_Texture** currAnimState;
	bool facingRight = true;
	float animatedFPS = 12.0f;
	void update() override;
	void updatePosition();
	void updateCollision();
	void updateAnimation();
};