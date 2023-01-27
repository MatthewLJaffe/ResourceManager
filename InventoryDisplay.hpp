#pragma once
#include "PlayerEntity.hpp"
#include "ResourceManager.hpp"
#include "InputManager.hpp"
#include "TextEntity.hpp"
#include "PreviewEntity.hpp"
#include <vector>

class PreviewEntity;

struct InventorySquare
{
	InventorySquare(std::string name, SDL_Texture* itemImg, PreviewEntity* preview);
	std::string itemName;
	bool usable;
	SDL_Texture* itemImg;
	PreviewEntity* preview;
};


class InventoryDisplay : public Entity
{
public:
	InventoryDisplay(float x, float y, float scale, SDL_Texture* tex, int sortOrder);
	void updateInventoryDisplay();
	void update() override;
	void render() override;
	void start();
	Vector2 itemPictureOffset;
	int selectedInventoryIdx = 0;
	TextEntity* equippedHandgunsText;
	TextEntity* equippedHandcannonsText;
	int equippedHandguns = 0;
	int equippedHandcannons = 0;
	std::vector<InventorySquare> inventorySquares;
private:
	void useResource(std::string name);
};