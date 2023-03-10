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
	/// <summary>
	/// checks for any enemy entities to collide with
	/// </summary>
	void updateCollision();
	void updateAnimation(float dT);
	//how long to wait in seconds before explosing
	float startDelay;
	Uint32 lastUpdateTime;
	std::vector<SDL_Texture*> explodeAnim;
	float animationFPS = 12;
	float currAnimFrameTime = 0;
	bool exploding = false;
	bool animating = false;
	size_t damageStartFrame;
	size_t currAnimIdx = 0;
	size_t damageEndFrame;
	float damage;
	float width;
	float height;
};