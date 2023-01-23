#pragma once
#include "GameState.hpp"
#include "ScrollBar.hpp"
#include "ButtonEntity.hpp"
#include "ResourceManager.hpp"
#include <functional>


class ResourceMenuState : public GameState
{
public:
	ResourceMenuState(std::string name);
	void start() override;
	std::string execute() override;
	std::string nextState;
};