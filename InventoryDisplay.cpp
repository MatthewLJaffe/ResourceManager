#include "InventoryDisplay.hpp"


#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

InventorySquare::InventorySquare(std::string name, SDL_Texture* itemImg, PreviewEntity* preview)
{
	this->itemName = name;
	this->itemImg = itemImg;
	this->usable = false;
	this->preview = preview;
	if (preview != NULL)
	{
		Game::Instance().AddEntity(preview, "MainGameState");
		preview->enabled = false;
	}
}

InventoryDisplay::InventoryDisplay(float x, float y, float scale, SDL_Texture* tex, int sortOrder) : Entity(x, y, scale, tex, sortOrder)
{
	itemPictureOffset = Vector2(2, 2);
}

void InventoryDisplay::start()
{
	inventorySquares.push_back(InventorySquare("spikes", Assets::Instance().img_SpikesUI, 
		 DBG_NEW PreviewEntity(0, 0, 4, Assets::Instance().img_ScrapPileTransparent, Assets::Instance().img_ScrapPileTransparent, 7, Vector2(12, -4))));
	inventorySquares.push_back(InventorySquare("handgun", Assets::Instance().img_GunUI, NULL));
	inventorySquares.push_back(InventorySquare("turret", Assets::Instance().img_TurretUI, 
		 DBG_NEW PreviewEntity(0 ,0, 4, Assets::Instance().img_TransparentTurretLeft, Assets::Instance().img_TransparentTurretRight, 7, Vector2(12 ,1))));
	inventorySquares.push_back(InventorySquare("bomb", Assets::Instance().img_BombUI, 
		 DBG_NEW PreviewEntity(0, 0, 4, Assets::Instance().img_BombPreview, Assets::Instance().img_BombPreview, 11, Vector2(6, -2))));
	inventorySquares.push_back(InventorySquare("handcannon", Assets::Instance().img_HandCannonUI, NULL));
	inventorySquares.push_back(InventorySquare("cannon", Assets::Instance().img_CannonUI, 
		 DBG_NEW PreviewEntity(0, 0, 4, Assets::Instance().img_CannonPreviewLeft, Assets::Instance().img_CannonPreviewRight, 7, Vector2(12, 1))));
	PlayerEntity* player = Game::Instance().GetMainGameState()->player;
	equippedHandgunsText =  DBG_NEW  TextEntity(240, 16, 1, "x" + std::to_string(player->getHandguns()), 24, {0,0,0}, Assets::Instance().font_Body, 10, 5);
	equippedHandcannonsText = DBG_NEW  TextEntity(240, 48, 1, "x" + std::to_string(player->getHandcannons()), 24, { 0,0,0 }, Assets::Instance().font_Body, 10, 5);
	Game::Instance().AddEntity(equippedHandcannonsText, "MainGameState");
	Game::Instance().AddEntity(equippedHandgunsText, "MainGameState");
	Game::Instance().AddEntity( DBG_NEW  Entity(72, -4, 4, Assets::Instance().img_GunUI, 5), "MainGameState");
	Game::Instance().AddEntity( DBG_NEW  Entity(72, 5, 4, Assets::Instance().img_HandCannonUI, 5), "MainGameState");
}

void InventoryDisplay::updateInventoryDisplay()
{
	for (int i = 0; i < inventorySquares.size(); i++)
	{
		if (ResourceManager::Instance().resourceMap[inventorySquares[i].itemName]->amount > 0)
			inventorySquares[i].usable = true;
		else
			inventorySquares[i].usable = false;
	}
	if (inventorySquares[selectedInventoryIdx].preview != NULL && inventorySquares[selectedInventoryIdx].usable)
	{
		inventorySquares[selectedInventoryIdx].preview->enabled = true;
	}
	if (inventorySquares[selectedInventoryIdx].preview != NULL && !inventorySquares[selectedInventoryIdx].usable)
	{
		inventorySquares[selectedInventoryIdx].preview->enabled = false;
	}

}

void InventoryDisplay::update()
{
	if (!enabled) return;
	int prevSelected = selectedInventoryIdx;
	if (InputManager::Instance().get1Down())
	{
		selectedInventoryIdx = 0;
	}
	else if (InputManager::Instance().get2Down())
	{
		selectedInventoryIdx = 1;
	}
	else if (InputManager::Instance().get3Down())
	{
		selectedInventoryIdx = 2;
	}
	else if (InputManager::Instance().get4Down())
	{
		selectedInventoryIdx = 3;
	}
	else if (InputManager::Instance().get5Down())
	{
		selectedInventoryIdx = 4;
	}
	else if (InputManager::Instance().get6Down())
	{
		selectedInventoryIdx = 5;
	}
	if (prevSelected != selectedInventoryIdx)
	{
		if (inventorySquares[prevSelected].preview != NULL) {
			inventorySquares[prevSelected].preview->enabled = false;
		}
		if (inventorySquares[selectedInventoryIdx].preview != NULL && inventorySquares[selectedInventoryIdx].usable)
		{
			inventorySquares[selectedInventoryIdx].preview->enabled = true;
		}
	}
	//activate item
	if (InputManager::Instance().getMouseReleased())
	{
		if (inventorySquares[selectedInventoryIdx].usable)
			useResource(inventorySquares[selectedInventoryIdx].itemName);
	}
}

void InventoryDisplay::render()
{
	if (!enabled) return;
	for (int i = 0; i < inventorySquares.size(); i++)
	{
		SDL_Texture* background;
		if (i == selectedInventoryIdx)
			background = Assets::Instance().img_Yellow;
		else
			background = Assets::Instance().img_White;

		SDL_Rect destRect = { (pos->x + itemPictureOffset.x + 18 * i) * scale, (pos->y + itemPictureOffset.y) * scale, 16 * scale, 16 * scale };
		RenderWindow::Instance().render(background, currentFrame, destRect, angle);
		if (inventorySquares[i].usable)
			RenderWindow::Instance().render(inventorySquares[i].itemImg, currentFrame, destRect, angle);
	}
	SDL_Rect destRect = { pos->x * scale, pos->y * scale, currentFrame.w * scale, currentFrame.h * scale };
	RenderWindow::Instance().render(tex, currentFrame, destRect, angle);
}

void InventoryDisplay::useResource(std::string name)
{
	PlayerEntity* player = Game::Instance().GetMainGameState()->player;
	if (name._Equal("handgun"))
	{
		player->incrementHandguns();
		equippedHandgunsText->updateText("x" + std::to_string(player->getHandguns()));
	}
	else if (name._Equal("handcannon"))
	{
		player->incrementHandcannons();
		equippedHandcannonsText->updateText("x" + std::to_string(player->getHandcannons()));
	}
	else if (name._Equal("turret"))
	{
		player->spawnTurret();
	}
	else if (name._Equal("spikes"))
	{
		player->spawnSpikes();
	}
	else if (name._Equal("bomb"))
	{
		player->spawnBomb();
	}
	else if (name._Equal("cannon"))
	{
		player->spawnCannon();
	}
	ResourceManager::Instance().deleteResource(name);
	updateInventoryDisplay();
}