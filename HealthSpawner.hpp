
#pragma once
#include "HeartEntity.hpp"

class HealthSpawner
{
public:
	HealthSpawner(int maxHealth, float spawnChance, float spawnTime);
	void update();
	//amount of health drops that can be present in the game at any time
	int maxHealth = 2;
	//milliseconds in game time since last health drop
	Uint32 lastUpdate = 0;
	//current health drops
	int currHealth = 0;
	//chance to spawn a health drop each time spawnTime has elapsed
	float spawnChance;
	//current time in seconds since last health drop spawned
	float currSpawnTime;
	float spawnTime = 30;
};
