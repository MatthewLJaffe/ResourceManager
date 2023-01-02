#include "InputManager.hpp"

InputManager& InputManager::Instance()
{
	static InputManager inputManager;
	return inputManager;
}

Vector2 InputManager::getMousePos()
{
	return *mousePos;
}

bool InputManager::getMouseDown()
{
	return mouseDown;
}

bool InputManager::getMousePressed()
{
	return mousePressed;
}



InputManager::~InputManager()
{
	delete mousePos;
}

void InputManager::handleInput(SDL_Event event)
{
	if (mousePressed)
		mousePressed = false;
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		int x, y;
		SDL_GetMouseState(&x, &y);
		mousePos->x = float(x);
		mousePos->y = float(y);
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (SDL_BUTTON_LEFT == event.button.button)
		{
			if (mouseDown)
				mousePressed = false;
			else
				mousePressed = true;
			mouseDown = true;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (SDL_BUTTON_LEFT == event.button.button)
		{
			mousePressed = false;
			mouseDown = false;
		}
		break;
	default:
		break;
	}
}

InputManager::InputManager()
{
	mousePos = new Vector2(0, 0);
}