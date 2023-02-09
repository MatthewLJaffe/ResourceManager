#pragma once
#include "Game.hpp"
#include "EnemyEntity.hpp"
#include "Utils.hpp"
#include "PlayerEntity.hpp"

/// <summary>
/// structure encapsulating how frequently enemies should be spawned based on horizontal distance of player from spawn
/// </summary>
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
	EnemySpawner(float baseSpawnRate, float spawnIncreaseRate, int waveAmount, float timeBetweenWaves, float waveIncreaseFactor, float maxSpawnDistance, float maxDistance, Entity* nextWaveIndicator, float minIndicatorX, float maxIndicatorX);
	void update();
private:
	void spawnEnemy();
	Entity* nextWaveIndicator;
	TextEntity* waveText;
	/// <summary>
	/// spawns enemy at random positoin between minX and maxX
	/// </summary>
	void spawnEnemy(float minX, float maxX);
	void spawnNextWave();
	float baseSpawnRate;
	//how much to increase the spawn rate every second of game time
	float spawnIncreaseRate;
	float timeBetweenWaves;
	//number of enemies to spawn this wave
	int waveAmount;
	//scales waveAmount each wave
	float waveIncreaseFactor;
	//max distance off screen enemies spawn
	float maxSpawnDistance;
	float minIndicatorX;
	float maxIndicatorX;
	int currWave = 0;
	float maxDistance;
	float spawnElapsedTime = 0;
	float increaseElapsedTime = 0;
	float waveElapsedTime = 0;
	Uint32 prevTime = 0;
	std::vector<DistanceSpawnFactor> distanceSpawnRateDistribution;
};