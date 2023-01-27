#pragma once
#include "WorldSpaceEntity.hpp"
#include "Assets.hpp"
#include "Game.hpp"
#include "Utils.hpp"

class BombEntity : public WorldSpaceEntity
{
public:
	BombEntity(float x, float y, float width, float height, int sortOrder, float damage);
	void update() override;
	void updateCollision();
	void updateAnimation(float dT);
	float startDelay;
	Uint32 lastUpdateTime;
	std::vector<SDL_Texture*> explodeAnim;
	float animationFPS = 12;
	float currAnimFrameTime = 0;
	bool exploding = false;
	bool animating = false;
	int damageStartFrame;
	int currAnimIdx = 0;
	int damageEndFrame;
	float damage;
	float width;
	float height;
};