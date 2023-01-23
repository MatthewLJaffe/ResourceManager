#pragma once
#include "GameState.hpp"
#include "InputManager.hpp"
#include "PlayerEntity.hpp"
#include "EnemyEntity.hpp"
#include "GameTransformer.hpp"
#include "ParallaxEntity.hpp"
#include "ResourceSpawner.hpp"

class ResourceSpawner;

class MainGameState : public GameState
{
public:
	MainGameState(std::string name, PlayerEntity* player, float minX, float maxX);
	void start() override;
	std::string execute() override;
	int maxLength = 200;
	PlayerEntity* player;
	ResourceSpawner* oreSpawner = NULL;
	float minX;
	float maxX;
};
