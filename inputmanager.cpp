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

float InputManager::getMouseWheelY()
{
	return mouseWheelY;
}

void InputManager::handleInput(SDL_Event event)
{
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
	case SDL_MOUSEWHEEL:
		mouseWheelY += event.wheel.y;
		if (mouseWheelY > maxWheel)
			mouseWheelY = maxWheel;
		if (mouseWheelY < minWheel)
			mouseWheelY = minWheel;
		break;
	default:
		break;
	}
}

InputManager::InputManager()
{
	mousePos = new Vector2(0, 0);
	mouseWheelY = 0;
}

InputManager::~InputManager()
{
	delete mousePos;
}
