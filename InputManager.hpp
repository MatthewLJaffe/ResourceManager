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
	float getMouseWheelY();
	bool getMousePressed();
	const int maxWheel = 0;
	const int minWheel = -2;

private:
	InputManager();
	~InputManager();
	int mouseWheelY;
	Vector2* mousePos;
	bool mouseDown = 0;
	bool mousePressed = 0;
};