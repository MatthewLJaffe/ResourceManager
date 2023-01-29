
#include "HealthSpawner.hpp"

HealthSpawner::HealthSpawner(int maxHealth, float spawnChance, float spawnTime)
{
	this->maxHealth = maxHealth;
	this->spawnChance = spawnChance;
	this->spawnTime = spawnTime;
	this->currHealth = 0;
	this->currSpawnTime = 0;
}

void HealthSpawner::update()
{
	Uint32 curr = Game::Instance().GetGameTime();
	if (lastUpdate == 0)
		lastUpdate = curr;
	float dT = (curr - lastUpdate) / 1000.0f;
	currSpawnTime += dT;
	if (currSpawnTime > spawnTime)
	{
		currSpawnTime = 0;
		if (currHealth >= maxHealth) return;
		if (utils::randomFloat(0, 1) > spawnChance) return;
		bool spawned = false;
		float maxX = Game::Instance().GetMainGameState()->maxX;
		float minX = Game::Instance().GetMainGameState()->minX;
		PlayerEntity* player = Game::Instance().GetMainGameState()->player;
		Vector2 spawnPos(0, 6);
		while (!spawned)
		{
			spawnPos.x = utils::randomFloat(minX, maxX);
			if (!player->posInView(spawnPos))
			{
				spawned = true;
			}
		}
		Game::Instance().AddEntity(new HeartEntity(spawnPos.x, spawnPos.y, 20, this));
		currHealth++;
	}
}
