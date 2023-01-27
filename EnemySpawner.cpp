#include "EnemySpawner.hpp"

DistanceSpawnFactor::DistanceSpawnFactor(float minX, float maxX, float spawnMultiplier)
{
	this->minDistance = minX;
	this->maxDistance = maxX;
	this->spawnMultiplier = spawnMultiplier;
}

EnemySpawner::EnemySpawner(float baseSpawnRate, float spawnIncreaseRate, int baseWaveAmount, float timeBetweenWaves, float waveIncreaseFactor, float maxSpawnDistance, float maxDistance)
{
	this->baseSpawnRate = baseSpawnRate;
	this->spawnIncreaseRate = spawnIncreaseRate;
	this->timeBetweenWaves = timeBetweenWaves;
	this->waveIncreaseFactor = waveIncreaseFactor;
	this->maxSpawnDistance = maxSpawnDistance;
	this->waveAmount = baseWaveAmount;
	this->maxDistance = maxDistance;
	distanceSpawnRateDistribution.push_back(DistanceSpawnFactor(0, maxDistance*.25f, 1));
	distanceSpawnRateDistribution.push_back(DistanceSpawnFactor(maxDistance *.25f, maxDistance *.5f, 1.25f));
	distanceSpawnRateDistribution.push_back(DistanceSpawnFactor(maxDistance *.5f, maxDistance *.75f, 1.75f));
	distanceSpawnRateDistribution.push_back(DistanceSpawnFactor(maxDistance *.75f, maxDistance *1.0f, 2.0f));
}

void EnemySpawner::update()
{
	float spawnFactor = 1;
	float playerDistance = abs(Game::Instance().GetMainGameState()->player->pos->x);
	for (int i = 0; i < distanceSpawnRateDistribution.size(); i++)
	{
		if (playerDistance > distanceSpawnRateDistribution[i].minDistance && playerDistance <= distanceSpawnRateDistribution[i].maxDistance)
		{
			spawnFactor = distanceSpawnRateDistribution[i].spawnMultiplier;
		}
	}
	//static float spawnElapsedTime = 0;
	//static float waveElapsedTime = 0;
	//static float increaseElapsedTime = 0;
	//static Uint32 prevTime = Game::Instance().GetGameTime();
	Uint32 current = Game::Instance().GetGameTime();
	if (prevTime == 0)
		prevTime = current;
	spawnElapsedTime += (current - prevTime) / 1000.0f;
	increaseElapsedTime += (current - prevTime) / 1000.0f;
	waveElapsedTime += (current - prevTime) / 1000.0f;
	if (increaseElapsedTime > 1)
	{
		baseSpawnRate += spawnIncreaseRate;
		increaseElapsedTime = 0;
	}
	if (spawnElapsedTime * baseSpawnRate * spawnFactor > 1)
	{
		spawnEnemy();
		spawnElapsedTime = 0;
	}
	if (waveElapsedTime >= timeBetweenWaves)
	{
		currWave++;
		waveAmount = static_cast<int>(floor(waveAmount * waveIncreaseFactor));
		for (int i = 0; i < waveAmount; i++)
		{
			spawnEnemy();
		}
		waveElapsedTime = 0;
	}
	prevTime = current;
}

void EnemySpawner::spawnEnemy()
{
	MainGameState* game = Game::Instance().GetMainGameState();
	float minSpawnRight = game->player->pos->x + 176;
	float maxSpawnRight = game->player->pos->x + 176 + maxSpawnDistance;
	if (maxSpawnRight > game->maxX)
		maxSpawnRight = game->maxX;
	float maxSpawnLeft = game->player->pos->x - 176;
	float minSpawnLeft = game->player->pos->x - 176 - maxSpawnDistance;
	if (minSpawnLeft < game->minX)
		minSpawnLeft = game->minX;
	float leftSpawnChance = (maxSpawnLeft - minSpawnLeft) / ((maxSpawnLeft - minSpawnLeft) + (maxSpawnRight - minSpawnRight));
	float rightSpawnChance = (maxSpawnRight - minSpawnRight) / ((maxSpawnLeft - minSpawnLeft) + (maxSpawnRight - minSpawnRight));
	bool spawnRight = utils::randomFloat(0.0f, 1.0f) < rightSpawnChance;
	float spawnX = 0;
	if (spawnRight)
	{
		spawnX = utils::randomFloat(minSpawnRight, maxSpawnRight);
	}
	else
		spawnX = utils::randomFloat(minSpawnLeft, maxSpawnLeft);
	Game::Instance().AddEntity(new EnemyEntity(spawnX, 0, 4, Assets::Instance().imgs_EnemyWalkRight[0], 3, 10.0f, 13, 23));
}