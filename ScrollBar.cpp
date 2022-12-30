#include "ScrollBar.hpp"
#include "Utils.hpp"

ScrollBar::ScrollBar(float x, float y, float scale, SDL_Texture* tex, int sortOrder)
	: Entity(x, y, scale, tex, sortOrder)
{
	minScrollY = y;
	maxScrollY = 161;
}

void ScrollBar::update()
{
	if (!enabled) return;
	bool pressedLastFrame = scrollBarPressed;
	if (!InputManager::Instance().getMouseDown()) {
		scrollBarPressed = false;
	}
	Vector2 mousePos = InputManager::Instance().getMousePos();
	if (InputManager::Instance().getMousePressed() && utils::inRect(mousePos.x, mousePos.y, pos->x * scale, pos->y * scale, currentFrame.w * scale, currentFrame.h * scale))
	{
		scrollBarPressed = true;
	}
	if (!scrollBarPressed) return;

	if (pressedLastFrame)
	{
		float yOffset = (mousePos.y - lastMousePos.y)/4;
		pos->y += yOffset;
		if (pos->y > maxScrollY)
			pos->y = maxScrollY;
		if (pos->y < minScrollY)
			pos->y = minScrollY;
	}
	lastMousePos = mousePos;
	//scroll text by computing offset
	ResourceListText::verticalOffset = 
		-utils::lerp(0, ResourceManager::Instance().getMaxTextOffset(), (pos->y - minScrollY) / (maxScrollY - minScrollY));
}

void ScrollBar::ResizeScrollBar(SDL_Texture* tex, int newMaxScrollY)
{
	this->tex = tex;
	maxScrollY = newMaxScrollY;
	SDL_QueryTexture(this->tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
	if (this->pos->y > maxScrollY)
		this->pos->y = maxScrollY;
}

ScrollBar::~ScrollBar()
{
	delete this->pos;
}