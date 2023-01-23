#include "MainGameState.hpp"

MainGameState::MainGameState(std::string name, PlayerEntity* player, float minX, float maxX) : GameState(name)
{
	this->player = player;
	this->minX = minX;
	this->maxX = maxX;
	oreSpawner = new ResourceSpawner("ore", .1, .001, .5, 20, 40);
}

void MainGameState::start()
{
	oreSpawner->start();
	entities.push_back(player);
	entities.push_back(new Entity(0, 0, 4, Assets::Instance().img_GameSky, 0));
	entities.push_back(new ParallaxEntity(0, 0, 4, Assets::Instance().img_GameBackground, 1, .25));
	entities.push_back(new ParallaxEntity(0, 0, 4, Assets::Instance().img_GameForeground, 2, .5));
	entities.push_back(new EnemyEntity(50, 0, 4, Assets::Instance().img_EnemyWalkRight[0], 4));
	int tiles = static_cast<int>(floor((maxX - minX) / 16));
	for (int i = 0; i < tiles; i++)
	{
		entities.push_back(new WorldSpaceEntity(i * 16 + minX + 8, 19, 4, Assets::Instance().img_FloorTile, 3));
	}
}

std::string MainGameState::execute()
{
	if (InputManager::Instance().getIPressed())
		return "ResourceMenuState";
	oreSpawner->update();
	GameTransformer::Instance().popTransformState();
	GameTransformer::Instance().translate(Vector2(player->pos->x * -1, 0));
	updateEntities();
	return name;
}