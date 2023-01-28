#pragma once
#include "GameState.hpp"
#include "Assets.hpp"
#include "ButtonEntity.hpp"
#include "Game.hpp"


class StartMenuState : public GameState
{
public:
	StartMenuState(std::string name);
	void start() override;
	std::string execute() override;
	std::string nextState;
};