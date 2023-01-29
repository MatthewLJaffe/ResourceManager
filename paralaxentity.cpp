#include "ParallaxEntity.hpp"

ParallaxEntity::ParallaxEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder, float scrollSpeed) : Entity(x, y, scale, tex, sortOrder)
{
	this->scrollSpeed = scrollSpeed;
	this->leftPos = Vector2(pos->x - 320, pos->y);
	this->rightPos = Vector2(pos->x + 320, pos->y);
	this->lastOffset = 0;
	
}

void ParallaxEntity::update()
{
	PlayerEntity* player = Game::Instance().GetMainGameState()->player;
	float minWorldX = Game::Instance().GetMainGameState()->minX;
	float maxWorldX = Game::Instance().GetMainGameState()->maxX;
	if (!enabled) return;
	if (player->pos->x > maxWorldX - 160 || player->pos->x < minWorldX + 160) return;
	this->pos->x -= player->pos->x * scrollSpeed - lastOffset;
	this->leftPos.x -= player->pos->x * scrollSpeed - lastOffset;
	this->rightPos.x -= player->pos->x * scrollSpeed - lastOffset;
	lastOffset = player->pos->x * scrollSpeed;

	if (leftPos.x < minX)
	{
		leftPos.x = pos->x;
		pos->x = rightPos.x;
		rightPos.x = maxX;
	}
	if (rightPos.x > maxX)
	{
		rightPos.x = this->pos->x;
		pos->x = leftPos.x;
		leftPos.x = minX;
	}
}

void ParallaxEntity::render()
{
	if (!enabled) return;
	SDL_Rect destRectLeft = { static_cast<int>(std::ceil(leftPos.x * scale)), utils::roundFloat(leftPos.y * scale), utils::roundFloat(currentFrame.w * scale), utils::roundFloat(currentFrame.h * scale) };
	SDL_Rect destRectRight = { static_cast<int>(std::floor(rightPos.x * scale)), utils::roundFloat(rightPos.y * scale), utils::roundFloat(currentFrame.w * scale), utils::roundFloat(currentFrame.h * scale) };
	SDL_Rect destRect = { utils::roundFloat(pos->x * scale), utils::roundFloat(pos->y * scale), utils::roundFloat(currentFrame.w * scale), utils::roundFloat(currentFrame.h * scale) };
	RenderWindow::Instance().render(tex, currentFrame, destRect, angle);
	RenderWindow::Instance().render(tex, currentFrame, destRectLeft, angle);
	RenderWindow::Instance().render(tex, currentFrame, destRectRight, angle);
}