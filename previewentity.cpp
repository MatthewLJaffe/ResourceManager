#include "PreviewEntity.hpp"

PreviewEntity::PreviewEntity(float x, float y, float scale, SDL_Texture* leftImg, SDL_Texture* rightImg, int sortOrder, Vector2 playerOffset)
	: WorldSpaceEntity(x, y, scale, leftImg, sortOrder)
{
	this->leftImg = leftImg;
	this->rightImg = rightImg;
	this->playerOffset = playerOffset;
}

void PreviewEntity::update()
{
	if (!enabled) return;
	PlayerEntity* player = Game::Instance().GetMainGameState()->player;
	if (player->facingRight)
	{
		if (playerOffset.x < 0)
		{
			playerOffset.x *= -1;
		}
		tex = rightImg;
	}
	else
	{
		if (playerOffset.x > 0)
		{
			playerOffset.x *= -1;
		}
		tex = leftImg;
	}
	this->pos = player->pos + playerOffset;
	WorldSpaceEntity::update();
}
