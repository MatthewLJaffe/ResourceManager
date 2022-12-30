#pragma once
#include "Entity.hpp"
#include "InputManager.hpp"
#include "ResourceManager.hpp"

class ScrollBar : public Entity
{
public:
	ScrollBar(float x, float y, float scale, SDL_Texture* tex, int sortOrder);
	void ResizeScrollBar(SDL_Texture* tex, int newMaxScrollY);
	void update() override;
private:
	bool scrollBarPressed = false;
	Vector2 lastMousePos;
	int textHeight = 40;
	float minScrollY;
	float maxScrollY;
	~ScrollBar();
};