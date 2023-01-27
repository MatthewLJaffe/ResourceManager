#pragma once
#include "WorldSpaceEntity.hpp"
#include "Assets.hpp"
#include "Game.hpp"
#include "Utils.hpp"

class SpikesEntity : public WorldSpaceEntity
{
public:
	SpikesEntity(float x, float y, float width, float height, int sortOrder, float damage, int damageTicks);
	void update() override;
	void destroySpikes();
	float width;
	int damageTicks;
	float height;
	float damage;
};