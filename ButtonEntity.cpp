#include "ButtonEntity.hpp"

ButtonEntity::ButtonEntity(float x, float y, float scale, SDL_Texture* defaultTex, SDL_Texture* pressedTex, int sortOrder, const std::function<void()>& pressedFunction)
	: Entity(x, y, scale, defaultTex, sortOrder)
{
	this->buttonDownTex = pressedTex;
	this->buttonPressedFunciton = pressedFunction;
}

void ButtonEntity::render()
{
	if (!enabled) return;
	SDL_Rect destRect = { utils::roundFloat(pos->x * scale), utils::roundFloat(pos->y * scale),utils::roundFloat(currentFrame.w * scale), utils::roundFloat(currentFrame.h * scale) };
	if (down)
		RenderWindow::Instance().render(buttonDownTex, currentFrame, destRect, angle);
	else
		RenderWindow::Instance().render(tex, currentFrame, destRect, angle);
}

void ButtonEntity::update()
{
	if (!enabled || (!InputManager::Instance().getMousePressed() && !InputManager::Instance().getMouseReleased())) return;
	pressed = false;
	bool mouseInButton = posInButton(InputManager::Instance().getMousePos());
	if (!mouseInButton)
	{
		down = false;
		return;
	}

	if (InputManager::Instance().getMousePressed())
	{
		down = true;
	}

	if (InputManager::Instance().getMouseReleased())
	{
		buttonPressedFunciton();
		down = false;
		pressed = true;
	}
}

bool ButtonEntity::posInButton(Vector2 pos)
{
	Vector2 screenPos = *this->pos * this->scale;
	SDL_Rect buttonRect{ utils::roundFloat(screenPos.x), utils::roundFloat(screenPos.y), utils::roundFloat(currentFrame.w * scale), utils::roundFloat(currentFrame.h * scale) };
	return (pos.x > screenPos.x && pos.x < screenPos.x + buttonRect.w &&
			pos.y > screenPos.y && pos.y < screenPos.y + buttonRect.h);
}