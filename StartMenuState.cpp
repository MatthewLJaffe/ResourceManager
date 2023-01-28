#include "StartMenuState.hpp"

StartMenuState::StartMenuState(std::string name) : GameState(name)
{}

void StartMenuState::start()
{
    entities.push_back(DBG_NEW Entity(0, 0, 4, Assets::Instance().img_StartMenuBackground, 0));
	auto pressedFunction = [&] { nextState = "MainGameState"; };
	entities.push_back(DBG_NEW ButtonEntity(136, 99, 4, Assets::Instance().img_StartMenuButton, Assets::Instance().img_StartMenuButtonPressed, 1, pressedFunction));
}

std::string StartMenuState::execute()
{
	nextState = name;
	updateEntities();
	return nextState;
}



