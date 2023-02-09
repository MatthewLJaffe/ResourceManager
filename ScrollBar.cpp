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
	Vector2 mousePos = InputManager::Instance().getMousePos();
	//mouse is outside of resource list 
	if (mousePos.x / 4 > 97) return;
	bool pressedLastFrame = scrollBarPressed;
	if (!InputManager::Instance().getMouseDown()) {
		scrollBarPressed = false;
	}
	if (InputManager::Instance().getMousePressed() && utils::inRect(mousePos.x, mousePos.y, pos.x * scale, pos.y * scale, currentFrame.w * scale, currentFrame.h * scale))
	{
		scrollBarPressed = true;
	}
	if (!scrollBarPressed) return;

	if (pressedLastFrame)
	{
		float yOffset = (mousePos.y - lastMousePos.y)/4;
		scrollTo(pos.y + yOffset);
	}
	lastMousePos = mousePos;
}

void ScrollBar::scrollTo(float yPos)
{
	if (!enabled) return;
	pos.y = yPos;
	if (pos.y > maxScrollY)
		pos.y = maxScrollY;
	if (pos.y < minScrollY)
		pos.y = minScrollY;
	//scroll text by computing offset
	ResourceListText::verticalOffset =
		-utils::lerp(0, ResourceManager::Instance().getMaxTextOffset(), (pos.y - minScrollY) / (maxScrollY - minScrollY));
}

void ScrollBar::ResizeScrollBar(SDL_Texture* tex, int newMaxScrollY)
{
	this->tex = tex;
	maxScrollY = static_cast<float>(newMaxScrollY);
	SDL_QueryTexture(this->tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
	if (this->pos.y > maxScrollY)
		this->pos.y = maxScrollY;
}