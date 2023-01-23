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

bool InputManager::getMouseReleased()
{
	return mouseReleased;
}

bool InputManager::getIPressed()
{
	return iPressed;
}

bool InputManager::getADown()
{
	return aDown;
}

bool InputManager::getDDown()
{
	return dDown;
}

float InputManager::getMouseWheelY()
{
	return mouseWheelY;
}

void InputManager::resetSingleFrameEvents()
{
	mousePressed = false;
	mouseReleased = false;
	iPressed = false;
}

void InputManager::handleInput(SDL_Event event)
{
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
			mouseReleased = true;
		}
		break;
	case SDL_MOUSEWHEEL:
		mouseWheelY += event.wheel.y;
		if (mouseWheelY > maxWheel)
			mouseWheelY = maxWheel;
		if (mouseWheelY < minWheel)
			mouseWheelY = minWheel;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_i)
		{
			if (!iDown)
				iPressed = true;
			iDown = true;
		}
		if (event.key.keysym.sym == SDLK_a)
		{
			aDown = true;
		}
		if (event.key.keysym.sym == SDLK_d)
		{
			dDown = true;
		}
		break;
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_i)
		{
			iPressed = false;
			iDown = false;
		}
		if (event.key.keysym.sym == SDLK_a)
		{
			aDown = false;
		}
		if (event.key.keysym.sym == SDLK_d)
		{
			dDown = false;
		}
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
