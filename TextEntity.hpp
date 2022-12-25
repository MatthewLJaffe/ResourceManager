#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Entity.hpp"
#include "RenderWindow.hpp"


class TextEntity : public Entity
{
public:
	TextEntity(float x, float y, std::string text, int size, TTF_Font* font, SDL_Color color, RenderWindow* renderWindow);
};