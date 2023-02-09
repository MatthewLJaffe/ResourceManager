#pragma once
#include <string>
#include <vector>
#include "Entity.hpp"
#include "Assets.hpp"

class GameState
{
public:
	GameState(std::string name);
	virtual ~GameState();
	std::string name;
	/// <summary>
	/// called before game state is executed
	/// </summary>
	virtual void start();
	/// <summary>
	/// calls the update and render functions of all entities in the game state
	/// </summary>
	virtual void updateEntities();
	/// <summary>
	/// updates the game state every frame
	/// </summary>
	/// <returns>the next game state to execute</returns>
	virtual std::string execute();
	/// <summary>
	/// called when this game state is no longer the one being executed
	/// </summary>
	virtual void onDeactivate();
	/// <summary>
	/// called when this state switches to being executed
	/// </summary>
	virtual void onActivate();
	/// <summary>
	/// the entities the current game state updates
	/// </summary>
	std::vector<Entity*> entities;
};