#pragma once
#include "WorldSpaceEntity.hpp";
#include "Assets.hpp"
#include "InputManager.hpp"
#include <cmath>

class PlayerEntity : public WorldSpaceEntity
{
public:
	PlayerEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder, float width, float height);
	float animatedFPS = 12.0f;
	Vector2 velocity;
	float walkSpeed = .6f;
	int currAnimIdx = 0;
	SDL_Texture** currAnimState;
	bool facingRight = true;
	void update() override;
	void updatePosition();
	void updateCollision();
	void updateAnimation();
	bool posInView(Vector2 pos);
	float width;
	float height;
};
