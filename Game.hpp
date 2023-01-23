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
#include "PlayerEntity.hpp"

class Game
{
public:
	void init();
	Game(const Game&) = delete;
	static Game& Instance();
	void RemoveEntity(Entity* entity);
	void RemoveAndDeleteEntity(Entity* entity);
	void RemoveEntity(Entity* entity, std::string gameState);
	void AddEntity(Entity* entity);
	void AddEntity(Entity* entity, std::string gameState);
	float minX = -1600.0f;
	float maxX = 1600.0f;
	PlayerEntity* player;
private:
	void update();
	std::map<std::string, GameState*> gameStateMap;
	Game();
	~Game();
	std::future<std::string> inputFuture;
	bool gameRunning;
	std::string currState;
};