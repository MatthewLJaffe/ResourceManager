#pragma once
#include "Game.hpp"
#include "EnemyEntity.hpp"
#include "Utils.hpp"
#include "PlayerEntity.hpp"


struct DistanceSpawnFactor
{
	DistanceSpawnFactor(float minX, float maxX, float spawnMultiplier);
	float minDistance;
	float maxDistance;
	float spawnMultiplier;
};


class EnemySpawner
{
public:
	EnemySpawner(float baseSpawnRate, float spawnIncreaseRate, int waveAmount, float timeBetweenWaves, float waveIncreaseFactor, float maxSpawnDistance, float maxDistance);
	void update();
private:
	void spawnEnemy();
	float baseSpawnRate;
	float spawnIncreaseRate;
	float timeBetweenWaves;
	float waveAmount;
	float waveIncreaseFactor;
	float maxSpawnDistance;
	int currWave = 0;
	float maxDistance;
	float spawnElapsedTime = 0;
	float increaseElapsedTime = 0;
	float waveElapsedTime = 0;
	Uint32 prevTime = 0;
	std::vector<DistanceSpawnFactor> distanceSpawnRateDistribution;
};