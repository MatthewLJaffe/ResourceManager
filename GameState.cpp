#include "GameState.hpp"

GameState::GameState(std::string name)
{
	this->name = name;
}

void GameState::updateEntities()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		entities[i]->update();
	}
}

std::string GameState::execute()
{
	updateEntities();
	return this->name;
}

void GameState::start()
{

}

void GameState::onActivate()
{

}

void GameState::onDeactivate()
{

}

GameState::~GameState()
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}
}