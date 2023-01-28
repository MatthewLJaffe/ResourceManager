#include "MainGameState.hpp"

MainGameState::MainGameState(std::string name) : GameState(name)
{
	this->player = player;
	this->minX = minX;
	this->maxX = maxX;
	this->healthSpawner = DBG_NEW HealthSpawner(2, .15, 30);
	oreSpawner = DBG_NEW ResourceSpawner("ore", .1, .001, .5, 20, 40, 0, maxX);
	gunPowderSpawner = DBG_NEW ResourceSpawner("gunpowder", .025, .001, .5, 0, 40, 90, maxX);
	inventoryDisplay = DBG_NEW InventoryDisplay(105, 0, 4, Assets::Instance().img_InventoryUI, 5);
	gameTime = 0;
	lastTime = 0;
}

void MainGameState::start()
{
	lastTime = SDL_GetTicks();

	Entity* indicator = DBG_NEW Entity(242, 12, 4, Assets::Instance().img_WaveMarker, 9);
	entities.push_back(indicator);
	entities.push_back(DBG_NEW Entity(241, 12, 4, Assets::Instance().img_WaveBar, 8));
	enemySpawner = DBG_NEW EnemySpawner(.1f, .003f, 6, 90, 1.5, 360, maxX, indicator, 242, 273);

	player = DBG_NEW PlayerEntity(0, 0, 4, Assets::Instance().img_PlayerRight, 4, 10, 22);
	oreSpawner->start();
	gunPowderSpawner->start();
	inventoryDisplay->start();
	entities.push_back(inventoryDisplay);
	entities.push_back(player);
	entities.push_back(DBG_NEW Entity(0, 0, 4, Assets::Instance().img_GameSky, 0));
	entities.push_back(DBG_NEW ParallaxEntity(0, 0, 4, Assets::Instance().img_GameBackground, 1, .25));
	entities.push_back(DBG_NEW ParallaxEntity(0, 0, 4, Assets::Instance().img_GameForeground, 2, .5));
	entities.push_back(DBG_NEW ResourceEntity(40, 7, 4, Assets::Instance().img_Ore, 4, "ore", 9, 8, oreSpawner));
	entities.push_back(DBG_NEW ResourceEntity(-40, 7, 4, Assets::Instance().img_Ore, 4, "ore", 9, 8, oreSpawner));
	entities.push_back(DBG_NEW ResourceEntity(-50, 7, 4, Assets::Instance().img_Ore, 4, "ore", 9, 8, oreSpawner));
	entities.push_back(DBG_NEW TurretEntity(32, 2, true, 10, 1, 23, 19, Assets::Instance().imgs_turretRight, 20, false));
	entities.push_back(DBG_NEW TurretEntity(-32, 2, false, 10, 1, 23, 19, Assets::Instance().imgs_turretLeft, 20, false));
	int tiles = static_cast<int>(floor((maxX - minX) / 16));
	for (int i = 0; i < tiles; i++)
	{
		entities.push_back(DBG_NEW WorldSpaceEntity(i * 16 + minX + 8, 19, 4, Assets::Instance().img_FloorTile, 3));
	}
	entities.push_back(DBG_NEW WorldSpaceEntity(minX + 17, -19, 4, Assets::Instance().img_CaveLeft, 3));
	entities.push_back(DBG_NEW WorldSpaceEntity(maxX - 17, -19, 4, Assets::Instance().img_CaveRight, 3));
	gameOverMenuEntities.push_back(DBG_NEW Entity(84, 35, 4, Assets::Instance().img_GameOverBackground, 8));
	survivedText = DBG_NEW TextEntity(104, 75, 4, "Time Survived: ", 6, { 255,255,255 }, Assets::Instance().font_Body, 30, 9);
	gameOverMenuEntities.push_back(survivedText);
	auto pressedFunction = [&] { 
		nextState = "StartMenuState";
		exitGame = true;
	};
	gameOverMenuEntities.push_back(DBG_NEW ButtonEntity(133, 92, 4, Assets::Instance().img_ContinueButton, Assets::Instance().img_ContinueButtonPressed, 9, pressedFunction));
	for (size_t i = 0; i < gameOverMenuEntities.size(); i++)
	{
		gameOverMenuEntities[i]->enabled = false;
		entities.push_back(gameOverMenuEntities[i]);
	}
}

std::string MainGameState::execute()
{
	if (InputManager::Instance().getIPressed())
		return "ResourceMenuState";
	oreSpawner->update();
	gunPowderSpawner->update();
	enemySpawner->update();
	healthSpawner->update();
	GameTransformer::Instance().popTransformState();
	Vector2 translatePos = Vector2(player->pos->x * -1, 0);
	if (translatePos.x > maxX - 160)
		translatePos.x = maxX - 160;
	if (translatePos.x < minX + 160)
		translatePos.x = minX + 160;
	GameTransformer::Instance().translate(translatePos);
	updateEntities();
	gameTime += SDL_GetTicks() - lastTime;
	lastTime = SDL_GetTicks();
	return nextState;
}

void MainGameState::onActivate()
{
	lastTime = SDL_GetTicks();
	inventoryDisplay->updateInventoryDisplay();
}

void MainGameState::onDeactivate()
{
	if (exitGame)
	{
		Game::Instance().ResetGame();
	}
}

Uint32 MainGameState::getGameTime()
{
	return gameTime;
}

void MainGameState::gameOver(float surviveTime)
{
	int minutes = floor(surviveTime / 60);
	int seconds = floor(surviveTime - 60 * static_cast<float>(minutes));
	std::string secondsFormatted = std::to_string(seconds);
	if (secondsFormatted.size() == 1)
		secondsFormatted = "0" + secondsFormatted;
	std::string timeSurvived = "Time Survived: " + std::to_string(minutes) + ":" + secondsFormatted;
	survivedText->updateText(timeSurvived);
	for (size_t i = 0; i < gameOverMenuEntities.size(); i++)
	{
		gameOverMenuEntities[i]->enabled = true;
	}
}

MainGameState::~MainGameState()
{
	delete healthSpawner;
	delete oreSpawner;
	delete gunPowderSpawner;
	delete enemySpawner;
}
