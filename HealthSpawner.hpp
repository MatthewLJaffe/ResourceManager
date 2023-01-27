
#pragma once
#include "HeartEntity.hpp"

class HealthSpawner
{
public:
	HealthSpawner(int maxHealth, float spawnChance, float spawnTime);
	void update();
	int maxHealth = 2;
	Uint32 lastUpdate = 0;
	int currHealth = 0;
	float spawnChance;
	float currSpawnTime;
	float spawnTime = 30;

};
