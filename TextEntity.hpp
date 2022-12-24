#pragma once
#include "Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

class TextEntity : public Entity
{
public:
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
};