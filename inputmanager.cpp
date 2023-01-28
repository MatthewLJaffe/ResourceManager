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

bool InputManager::get1Down()
{
	return alpha_1Down;
}

bool InputManager::get2Down()
{
	return alpha_2Down;
}

bool InputManager::get3Down()
{
	return alpha_3Down;
}

bool InputManager::get4Down()
{
	return alpha_4Down;
}

bool InputManager::get5Down()
{
	return alpha_5Down;
}

bool InputManager::get6Down()
{
	return alpha_6Down;
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
		if (event.key.keysym.sym == SDLK_1)
		{
			alpha_1Down = true;
		}
		if (event.key.keysym.sym == SDLK_2)
		{
			alpha_2Down = true;
		}
		if (event.key.keysym.sym == SDLK_3)
		{
			alpha_3Down = true;
		}
		if (event.key.keysym.sym == SDLK_4)
		{
			alpha_4Down = true;
		}
		if (event.key.keysym.sym == SDLK_5)
		{
			alpha_5Down = true;
		}
		if (event.key.keysym.sym == SDLK_6)
		{
			alpha_6Down = true;
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
		if (event.key.keysym.sym == SDLK_1)
		{
			alpha_1Down = false;
		}
		if (event.key.keysym.sym == SDLK_2)
		{
			alpha_2Down = false;
		}
		if (event.key.keysym.sym == SDLK_3)
		{
			alpha_3Down = false;
		}
		if (event.key.keysym.sym == SDLK_4)
		{
			alpha_4Down = false;
		}
		if (event.key.keysym.sym == SDLK_5)
		{
			alpha_5Down = false;
		}
		if (event.key.keysym.sym == SDLK_6)
		{
			alpha_6Down = false;
		}
		break;
	default:
		break;
	}
}

InputManager::InputManager()
{
	mousePos = DBG_NEW Vector2(0, 0);
	mouseWheelY = 0;
}

InputManager::~InputManager()
{
	delete mousePos;
}
