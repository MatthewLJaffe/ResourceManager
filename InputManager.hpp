#pragma once
#include <SDL.h>
#include "Vector2.hpp"

class InputManager
{
public:
	static InputManager& Instance();
	InputManager(InputManager&) = delete;
	void handleInput(SDL_Event event);
	Vector2 getMousePos();
	bool getMouseDown();
	bool getMousePressed();

private:
	InputManager();
	~InputManager();
	Vector2* mousePos;
	bool mouseDown = 0;
	bool mousePressed = 0;
};