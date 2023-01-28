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
	virtual void start();
	virtual void updateEntities();
	virtual std::string execute();
	virtual void onDeactivate();
	virtual void onActivate();
	std::vector<Entity*> entities;
};