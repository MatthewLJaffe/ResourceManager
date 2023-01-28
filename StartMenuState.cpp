#include "StartMenuState.hpp"

StartMenuState::StartMenuState(std::string name) : GameState(name)
{}

void StartMenuState::start()
{
    entities.push_back(DBG_NEW Entity(0, 0, 4, Assets::Instance().img_StartMenuBackground, 0));
	auto pressedFunction = [&] { nextState = "MainGameState"; };
	auto exitButton = [] {Game::Instance().QuitGame(); };
	entities.push_back(DBG_NEW ButtonEntity(136, 80, 4, Assets::Instance().img_StartMenuButton, Assets::Instance().img_StartMenuButtonPressed, 2, pressedFunction));
	entities.push_back(DBG_NEW ButtonEntity(136, 110, 4, Assets::Instance().img_QuitButton, Assets::Instance().img_QuitButtonPressed, 2, exitButton));
}

std::string StartMenuState::execute()
{
	nextState = name;
	updateEntities();
	return nextState;
}
