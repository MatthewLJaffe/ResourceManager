#pragma once
#include "Entity.hpp"
#include <vector>
#include <future>
#include <thread>
#include "ResourceListText.hpp"
#include "ScrollBar.hpp"
#include "ResourceManager.hpp"
#include "InputManager.hpp"
#include "ArrowEntity.hpp"
#include "DisplayNode.hpp"
#include "GameState.hpp"
#include "ResourceMenuState.hpp"
#include "StartMenuState.hpp"
#include "MainGameState.hpp"


class MainGameState;

class Game
{
public:
	void init();
	Game(const Game&) = delete;
	static Game& Instance();
	/// <summary>
	/// removes entity from current game state
	/// </summary>
	/// <param name="entity">entity to remove</param>
	void RemoveEntity(Entity* entity);
	/// <summary>
	/// removes entity from current game state and calls delete on it
	/// </summary>
	/// <param name="entity">entity to remove</param>
	void RemoveAndDeleteEntity(Entity* entity);
	/// <summary>
	/// removes entity from the specified game state
	/// </summary>
	/// <param name="entity">entity to remove</param>
	/// <param name="gameState">game state to remove entity from</param>
	void RemoveEntity(Entity* entity, std::string gameState);
	/// <summary>
	/// adds entity to current game state
	/// </summary>
	/// <param name="entity">entity to add</param>
	void AddEntity(Entity* entity);
	/// <summary>
	/// adds entity to specified game state
	/// </summary>
	/// <param name="entity">entity to add</param>
	/// <param name="gameState">gamestate to add entity to</param>
	void AddEntity(Entity* entity, std::string gameState);
	/// <summary>
	/// restarts the main game state
	/// </summary>
	void ResetGame();
	/// <summary>
	/// exits the game
	/// </summary>
	void QuitGame();
	MainGameState* GetMainGameState();
	Uint32 GetGameTime();
private:
	void update();
	std::map<std::string, GameState*> gameStateMap;
	Game();
	~Game();
	std::future<std::string> inputFuture;
	bool gameRunning = false;
	std::string currState;
};