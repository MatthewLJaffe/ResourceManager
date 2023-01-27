#pragma once
#include "Game.hpp"
#include "ResourceEntity.hpp"
#include "Utils.hpp"

struct DistanceChance
{
	DistanceChance(float minX, float maxX, float spawnChance);
	float minDistance;
	float maxDistance;
	float spawnChance;
};

class ResourceSpawner
{
public:
	ResourceSpawner(std::string resourceName, float spawnRate, float spawnIncreaseRate, float replacementChance, int startResources, int maxResource, float spawnDelay, float maxX);
	void start();
	void update();
	void spawnResource();
	void resourceConsumed();
	int currResources = 0;

private:
	std::vector<DistanceChance> spawnDistribution;
	std::string resourceName;
	int startResources;
	float resourceSpawnRate;
	float spawnIncreaseRate;
	float replacementChance;
	float spawnDelay;
	int maxResources;
	int initialMaxResources;
	float initialResourceSpawnRate;
	float maxDistance;
	float spawnElapsedTime;
	float increaseElapsedTime;
	float delayElapsedTime;
	bool spawning = false;
	Uint32 lastUpdateTime;
};