#include "ResourceSpawner.hpp"

DistanceChance::DistanceChance(float minX, float maxX, float spawnChance)
{
	this->minDistance = minX;
	this->maxDistance = maxX;
	this->spawnChance = spawnChance;
}

ResourceSpawner::ResourceSpawner(std::string resourceName, float spawnRate, float spawnIncreaseRate, float replacementChance, int startResources, int maxResource)
{
	this->resourceName = resourceName;
	this->resourceSpawnRate = spawnRate;
	this->replacementChance = replacementChance;
	this->maxResources = maxResource;
	this->spawnIncreaseRate = spawnIncreaseRate;
	this->startResources = startResources;
	this->initialMaxResources = maxResource;
	this->initialResourceSpawnRate = spawnRate;
	if (resourceName._Equal("ore"))
	{
		float maxDistance = Game::Instance().maxX;
		spawnDistribution.push_back(DistanceChance(0, maxDistance * .25, .1));
		spawnDistribution.push_back(DistanceChance(maxDistance * .25, maxDistance * .5, .2));
		spawnDistribution.push_back(DistanceChance(maxDistance * .5, maxDistance * .75, .3));
		spawnDistribution.push_back(DistanceChance(maxDistance * .75, maxDistance * 1, .4));
	}
	currResources = 0;
}

void ResourceSpawner::start()
{
	for (int i = 0; i < startResources; i++)
	{
		spawnResource();
	}
}


void ResourceSpawner::update()
{
	static float spawnElapsedTime = 0;
	static float increaseElapsedTime = 0;
	static Uint32 prevTime = SDL_GetTicks();
	Uint32 current = SDL_GetTicks();
	spawnElapsedTime += (current - prevTime) / 1000.0f;
	increaseElapsedTime += (current - prevTime) / 1000.0f;
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
	prevTime = current;
}

void ResourceSpawner::spawnResource()
{
	if (currResources >= maxResources) return;
	if (resourceName._Equal("ore"))
	{
		bool foundSpawn = false;
		float spawnX = 0;
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
			if (!Game::Instance().player->posInView(Vector2(spawnX, 0)))
			{
				foundSpawn = true;
			}
		}
		
		ResourceEntity* newResource = new ResourceEntity(spawnX, 7, 4, Assets::Instance().img_Ore, 4, "ore", 9, 8, this);
		Game::Instance().AddEntity(newResource, "MainGameState");
		currResources++;
	}
}

void ResourceSpawner::resourceConsumed()
{
	currResources--;
	if (utils::randomFloat(0.0f, 1.0f) <= replacementChance)
		spawnResource();
}