#include "EnemySpawner.hpp"

DistanceSpawnFactor::DistanceSpawnFactor(float minX, float maxX, float spawnMultiplier)
{
	this->minDistance = minX;
	this->maxDistance = maxX;
	this->spawnMultiplier = spawnMultiplier;
}

EnemySpawner::EnemySpawner(float baseSpawnRate, float spawnIncreaseRate, int baseWaveAmount, float timeBetweenWaves, float waveIncreaseFactor, float maxSpawnDistance, float maxDistance, Entity* nextWaveIndicator, float minIndicatorX, float maxIndicatorX)
{
	this->baseSpawnRate = baseSpawnRate;
	this->spawnIncreaseRate = spawnIncreaseRate;
	this->timeBetweenWaves = timeBetweenWaves;
	this->waveIncreaseFactor = waveIncreaseFactor;
	this->maxSpawnDistance = maxSpawnDistance;
	this->waveAmount = baseWaveAmount;
	this->maxDistance = maxDistance;
	this->nextWaveIndicator = nextWaveIndicator;
	this->minIndicatorX = minIndicatorX;
	this->maxIndicatorX = maxIndicatorX;
	waveText = new TextEntity(980, 12, 1, "Wave 0", 24, { 0, 0, 0 }, Assets::Instance().font_Body, 30, 9);
	Game::Instance().AddEntity(waveText, "MainGameState");
	distanceSpawnRateDistribution.push_back(DistanceSpawnFactor(0, maxDistance*.25f, .75));
	distanceSpawnRateDistribution.push_back(DistanceSpawnFactor(maxDistance *.25f, maxDistance *.5f, 1.0f));
	distanceSpawnRateDistribution.push_back(DistanceSpawnFactor(maxDistance *.5f, maxDistance *.75f, 1.5f));
	distanceSpawnRateDistribution.push_back(DistanceSpawnFactor(maxDistance *.75f, maxDistance *1.0f, 1.75f));
}

void EnemySpawner::update()
{
	float spawnFactor = 1;
	float playerDistance = abs(Game::Instance().GetMainGameState()->player->pos->x);
	for (size_t i = 0; i < distanceSpawnRateDistribution.size(); i++)
	{
		if (playerDistance > distanceSpawnRateDistribution[i].minDistance && playerDistance <= distanceSpawnRateDistribution[i].maxDistance)
		{
			spawnFactor = distanceSpawnRateDistribution[i].spawnMultiplier;
		}
	}
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
	if (spawnElapsedTime * baseSpawnRate * spawnFactor >= 1)
	{
		spawnEnemy();
		spawnElapsedTime = 0;
	}
	if (waveElapsedTime >= timeBetweenWaves)
	{
		spawnNextWave();
	}
	nextWaveIndicator->pos->x = utils::lerp(minIndicatorX, maxIndicatorX, waveElapsedTime / timeBetweenWaves);
	prevTime = current;
}

void EnemySpawner::spawnEnemy(float minX, float maxX)
{
	float spawnX = utils::randomFloat(minX, maxX);
	Game::Instance().AddEntity(new EnemyEntity(spawnX, 0, 4, Assets::Instance().imgs_EnemyWalkRight[0], 5, 10.0f, 13, 23));
}


void EnemySpawner::spawnEnemy()
{
	MainGameState* game = Game::Instance().GetMainGameState();
	float minSpawnRight = game->player->pos->x + 176;
	float maxSpawnRight = game->player->pos->x + 176 + maxSpawnDistance;
	float maxSpawnLeft = game->player->pos->x - 176;
	float minSpawnLeft = game->player->pos->x - 176 - maxSpawnDistance;
	float maxSpawnSideChance = .8;
	float rightSpawnChance = abs(game->player->pos->x - game->minX) / (game->maxX - game->minX);
	std::vector<TurretEntity*> turrets = Game::Instance().GetMainGameState()->turrets;
	int tries = 1000;
	float spawnX = 0;
	while (tries > 0)
	{
		if (rightSpawnChance > maxSpawnSideChance)
			rightSpawnChance = .8;
		bool spawnRight = utils::randomFloat(0.0f, 1.0f) < rightSpawnChance;
		if (spawnRight)
		{
			spawnX = utils::randomFloat(minSpawnRight, maxSpawnRight);
		}
		else
			spawnX = utils::randomFloat(minSpawnLeft, maxSpawnLeft);
		bool obstruction = false;
		for (size_t i = 0; i < turrets.size(); i++)
		{
			if (abs(turrets[i]->pos->x - spawnX) < turrets[i]->width)
			{
				obstruction = true;
				break;
			}
		}
		if (!obstruction)
			break;
		maxSpawnRight += 20;
		minSpawnLeft -= 20;
		tries--;
	}
	if (tries == 0) return;
	Game::Instance().AddEntity(new EnemyEntity(spawnX, 0, 4, Assets::Instance().imgs_EnemyWalkRight[0], 5, 10.0f, 13, 23));
}

void EnemySpawner::spawnNextWave()
{
	currWave++;
	waveText->updateText("Wave " + std::to_string(currWave));
	waveAmount = static_cast<int>(std::floor(waveAmount * waveIncreaseFactor));
	float offsetX = 100 + waveAmount / 10;
	MainGameState* game = Game::Instance().GetMainGameState();
	float maxX = game->maxX;
	float minX = game->minX;
	if (offsetX > 300)
		offsetX = 300;
	for (int i = 0; i < waveAmount; i++)
	{
		if (.5f > utils::randomFloat(0, 1))
			spawnEnemy(maxX, maxX + offsetX);
		else
			spawnEnemy(minX - offsetX, minX);
	}
	waveElapsedTime = 0;
}