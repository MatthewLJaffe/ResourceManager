#pragma once
#include "GameState.hpp"
#include "InputManager.hpp"
#include "EnemyEntity.hpp"
#include "GameTransformer.hpp"
#include "ParallaxEntity.hpp"
#include "ResourceSpawner.hpp"
#include "EnemySpawner.hpp"
#include "InventoryDisplay.hpp"
#include "vector"
#include "HealthSpawner.hpp"

class HealthSpawner;
class ResourceSpawner;
class EnemySpawner;
class InventoryDisplay;
class EnemyEntity;
class PlayerEntity;
class TurretEntity;

class MainGameState : public GameState
{
public:
	MainGameState(std::string name);
	~MainGameState();
	void start() override;
	std::string execute() override;
	void onActivate() override;
	void onDeactivate() override;
	Uint32 getGameTime();
	void gameOver(float survivalTime);
	bool exitGame = false;
	std::string nextState = "MainGameState";
	int maxLength = 200;
	PlayerEntity* player;
	ResourceSpawner* oreSpawner;
	ResourceSpawner* gunPowderSpawner;
	EnemySpawner* enemySpawner;
	HealthSpawner* healthSpawner;
	InventoryDisplay* inventoryDisplay;
	TextEntity* survivedText;
	std::vector<EnemyEntity*> enemies;
	std::vector<TurretEntity*> turrets;
	std::vector<Entity*> gameOverMenuEntities;
	float minX = -1600;
	float maxX = 1600;


private:
	Uint32 gameTime = 0;
	Uint32 lastTime;
};
