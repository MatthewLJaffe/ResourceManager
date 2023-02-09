#pragma once
#include "WorldSpaceEntity.hpp"
#include "PlayerEntity.hpp"
#include "Game.hpp"

class PreviewEntity : public WorldSpaceEntity
{
/// <summary>
/// used to display where item from currently selected inventory square will be placed
/// </summary>
public:
	PreviewEntity(float x, float y, float scale, SDL_Texture* leftImg, SDL_Texture* rightImg, int sortOrder, Vector2 playerOffset);
	SDL_Texture* leftImg;
	SDL_Texture* rightImg;
	Vector2 playerOffset;
	void update() override;
};