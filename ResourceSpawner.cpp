#include "ResourceSpawner.hpp"

DistanceChance::DistanceChance(float minX, float maxX, float spawnChance)
{
	this->minDistance = minX;
	this->maxDistance = maxX;
	this->spawnChance = spawnChance;
}

ResourceSpawner::ResourceSpawner(std::string resourceName, float spawnRate, float spawnIncreaseRate, float replacementChance, int startResources, int maxResource, float spawnDelay, float maxX)
{
	this->resourceName = resourceName;
	this->resourceSpawnRate = spawnRate;
	this->initialResourceSpawnRate = spawnRate;
	this->replacementChance = replacementChance;
	this->maxResources = maxResource;
	this->spawnDelay = spawnDelay;
	this->spawnIncreaseRate = spawnIncreaseRate;
	this->startResources = startResources;
	this->initialMaxResources = maxResource;
	this->maxDistance = maxX;
	if (resourceName._Equal("ore"))
	{
		spawnDistribution.push_back(DistanceChance(0, maxDistance * .25, .1));
		spawnDistribution.push_back(DistanceChance(maxDistance * .25, maxDistance * .5, .2));
		spawnDistribution.push_back(DistanceChance(maxDistance * .5, maxDistance * .75, .3));
		spawnDistribution.push_back(DistanceChance(maxDistance * .75, maxDistance * 1, .4));
	}
	if (resourceName._Equal("gunpowder"))
	{
		spawnDistribution.push_back(DistanceChance(0, maxDistance * .25, 0));
		spawnDistribution.push_back(DistanceChance(maxDistance * .25, maxDistance * .5, .15));
		spawnDistribution.push_back(DistanceChance(maxDistance * .5, maxDistance * .75, .35));
		spawnDistribution.push_back(DistanceChance(maxDistance * .75, maxDistance * 1, .45));
	}
	currResources = 0;
	spawnElapsedTime = 0;
	increaseElapsedTime = 0;
	delayElapsedTime = 0;
	spawning = false;
}

void ResourceSpawner::start()
{
	lastUpdateTime = Game::Instance().GetGameTime();
	for (int i = 0; i < startResources; i++)
	{
		spawnResource();
	}
}


void ResourceSpawner::update()
{
	Uint32 current = Game::Instance().GetGameTime();
	float dT = (current - lastUpdateTime) / 1000.0f;
	delayElapsedTime += dT;
	if (delayElapsedTime > spawnDelay)
		spawning = true;
	if (spawning)
	{
		spawnElapsedTime += dT;
		increaseElapsedTime += dT;
		if (increaseElapsedTime > 1)
		{
			resourceSpawnRate += spawnIncreaseRate;
			maxResources = static_cast<int>(initialMaxResources * floor(resourceSpawnRate / initialResourceSpawnRate));
			increaseElapsedTime = 0;
		}
		if (spawnElapsedTime * resourceSpawnRate > 1)
		{
			spawnResource();
			spawnElapsedTime = 0;
		}
	}
	lastUpdateTime = current;
}

void ResourceSpawner::spawnResource()
{
	if (currResources >= maxResources) return;
	bool foundSpawn = false;
	float spawnX = 0;
	float minPlayerDistance = 600;
	PlayerEntity* player = Game::Instance().GetMainGameState()->player;
	while (!foundSpawn)
	{
		DistanceChance spawnDistance = spawnDistribution[0];
		float rand = utils::randomFloat(0.0f, 1.0f);
		for (int i = 0; i < spawnDistribution.size(); i++)
		{
			if (spawnDistribution[i].spawnChance >= rand)
			{
				spawnDistance = spawnDistribution[i];
				break;
			}
			rand -= spawnDistribution[i].spawnChance;
		}
		float minX = spawnDistance.minDistance;
		float maxX = spawnDistance.maxDistance;
		spawnX = utils::randomFloat(minX, maxX);
		if (utils::randomFloat(0.0f, 1.0f) >= .5f)
		{
			spawnX *= -1;
		}
		if (abs(player->pos->x - spawnX) > minPlayerDistance)
		{
			foundSpawn = true;
		}
	}
	if (resourceName._Equal("ore"))
	{
		ResourceEntity* newResource = DBG_NEW ResourceEntity(spawnX, 7, 4, Assets::Instance().img_Ore, 4, resourceName, 9, 8, this);
		Game::Instance().AddEntity(newResource, "MainGameState");
	}
	else if (resourceName._Equal("gunpowder"))
	{
		ResourceEntity* newResource = DBG_NEW ResourceEntity(spawnX, 7, 4, Assets::Instance().img_GunPowder, 4, resourceName, 12, 10, this);
		Game::Instance().AddEntity(newResource, "MainGameState");
	}
	currResources++;
}

void ResourceSpawner::resourceConsumed()
{
	currResources--;
	if (utils::randomFloat(0.0f, 1.0f) <= replacementChance)
		spawnResource();
}