#pragma once
#include "Entity.hpp"
#include <functional>
#include "InputManager.hpp"

class ButtonEntity : public Entity
{
public:
	bool pressed = false;
	bool down = false;
	std::function<void()> buttonPressedFunciton;
	SDL_Texture* buttonDownTex;
	ButtonEntity(float x, float y, float scale, SDL_Texture* defaultTex, SDL_Texture* pressedTex, int sortOrder, const std::function<void()>& pressedFunction);
	void render() override;
	void update() override;
	bool posInButton(Vector2 pos);
};