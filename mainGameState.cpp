#include "MainGameState.hpp"

MainGameState::MainGameState(std::string name) : GameState(name)
{
	this->player = player;
	this->minX = minX;
	this->maxX = maxX;
	oreSpawner = new ResourceSpawner("ore", .1, .001, .5, 20, 40, 0, maxX);
	gunPowderSpawner = new ResourceSpawner("gunpowder", .1, .001, .5, 20, 40, 0, maxX);
	enemySpawner = new EnemySpawner(.2f, .005f, 5, 60, 1.5, 360, maxX);
	inventoryDisplay = new InventoryDisplay(105, 0, 4, Assets::Instance().img_InventoryUI, 5);
	gameTime = 0;
	lastTime = 0;
}

void MainGameState::start()
{
	lastTime = SDL_GetTicks();
	player = new PlayerEntity(0, 0, 4, Assets::Instance().img_PlayerRight, 3, 10, 22);
	oreSpawner->start();
	gunPowderSpawner->start();
	inventoryDisplay->start();
	entities.push_back(inventoryDisplay);
	entities.push_back(player);
	entities.push_back(new Entity(0, 0, 4, Assets::Instance().img_GameSky, 0));
	entities.push_back(new ParallaxEntity(0, 0, 4, Assets::Instance().img_GameBackground, 1, .25));
	entities.push_back(new ParallaxEntity(0, 0, 4, Assets::Instance().img_GameForeground, 2, .5));
	int tiles = static_cast<int>(floor((maxX - minX) / 16));
	for (int i = 0; i < tiles; i++)
	{
		entities.push_back(new WorldSpaceEntity(i * 16 + minX + 8, 19, 4, Assets::Instance().img_FloorTile, 3));
	}
	gameOverMenuEntities.push_back(new Entity(84, 35, 4, Assets::Instance().img_GameOverBackground, 8));
	survivedText = new TextEntity(104, 75, 4, "Time Survived: ", 6, { 255,255,255 }, Assets::Instance().font_Body, 30, 9);
	gameOverMenuEntities.push_back(survivedText);
	auto pressedFunction = [&] { 
		nextState = "StartMenuState";
		exitGame = true;
	};
	gameOverMenuEntities.push_back(new ButtonEntity(133, 92, 4, Assets::Instance().img_ContinueButton, Assets::Instance().img_ContinueButtonPressed, 9, pressedFunction));
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
	GameTransformer::Instance().popTransformState();
	GameTransformer::Instance().translate(Vector2(player->pos->x * -1, 0));
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
	delete oreSpawner;
	delete gunPowderSpawner;
	delete enemySpawner;
	for (int i = 0; i < entities.size(); i++)
	{
		delete entities[i];
	}
}
