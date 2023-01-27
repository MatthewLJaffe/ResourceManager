
#pragma once
#include "WorldSpaceEntity.hpp"
#include "Assets.hpp"
#include "Game.hpp"
#include "Utils.hpp"

class HealthSpawner;

class HeartEntity : public WorldSpaceEntity
{
public:
	HeartEntity(float x, float y, float healthAmount, HealthSpawner* spawner);
	void update() override;
private:
	float healthAmount;
	float width;
	float height;
	HealthSpawner* spawner;
};
