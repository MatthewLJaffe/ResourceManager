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

/// <summary>
/// the state where the game is played
/// </summary>
class MainGameState : public GameState
{
public:
	MainGameState(std::string name);
	~MainGameState() override;
	void start() override;
	std::string execute() override;
	void onActivate() override;
	void onDeactivate() override;
	/// <summary>
	/// returns the time in miliseconds since the start of the game only updates when in the main game state
	/// </summary>
	/// <returns></returns>
	Uint32 getGameTime();
	/// <summary>
	/// function that ends the current game
	/// </summary>
	/// <param name="survivalTime">used to display the amount of time survived on the game over screen</param>
	void gameOver(float survivalTime);
	bool exitGame = false;
	/// <summary>
	/// the next game state to execute next frame
	/// </summary>
	std::string nextState = "MainGameState";
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
