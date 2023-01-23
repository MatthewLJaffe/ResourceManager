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
	bool getMouseReleased();
	bool getIPressed();
	bool getADown();
	bool getDDown();
	void resetSingleFrameEvents();
	const int maxWheel = 0;
	const int minWheel = -2;

private:
	InputManager();
	~InputManager();
	int mouseWheelY;
	Vector2* mousePos;
	bool mouseDown = false;
	bool mousePressed = false;
	bool mouseReleased = false;
	bool aDown;
	bool dDown;
	bool iPressed;
	bool iDown;
};