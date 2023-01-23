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
	if (!enabled) return;
	this->pos->x -= Game::Instance().player->pos->x * scrollSpeed - lastOffset;
	this->leftPos.x -= Game::Instance().player->pos->x * scrollSpeed - lastOffset;
	this->rightPos.x -= Game::Instance().player->pos->x * scrollSpeed - lastOffset;
	lastOffset = Game::Instance().player->pos->x * scrollSpeed;

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
	SDL_Rect destRectLeft = { leftPos.x * scale, leftPos.y * scale, currentFrame.w * scale, currentFrame.h * scale };
	SDL_Rect destRectRight = { rightPos.x * scale, rightPos.y * scale, currentFrame.w * scale, currentFrame.h * scale };
	SDL_Rect destRect = { pos->x * scale, pos->y * scale, currentFrame.w * scale, currentFrame.h * scale };
	RenderWindow::Instance().render(tex, currentFrame, destRect, angle);
	RenderWindow::Instance().render(tex, currentFrame, destRectLeft, angle);
	RenderWindow::Instance().render(tex, currentFrame, destRectRight, angle);
}