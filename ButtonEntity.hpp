#pragma once
#include "Entity.hpp"
#include <functional>
#include "InputManager.hpp"

class ButtonEntity : public Entity
{
public:
	//true the frame the mouse is released after the button is down false otherwise
	bool pressed = false;
	//true while the button is down false otherwise
	bool down = false;
	//texture to display when the button is being pressed down
	SDL_Texture* buttonDownTex;
	ButtonEntity(float x, float y, float scale, SDL_Texture* defaultTex, SDL_Texture* pressedTex, int sortOrder, const std::function<void()>& pressedFunction);
	void render() override;
	void update() override;
	bool posInButton(Vector2 pos);
private:
	/// <summary>
	/// callback to execute when the button is pressed
	/// </summary>
	std::function<void()> buttonPressedFunciton;
};