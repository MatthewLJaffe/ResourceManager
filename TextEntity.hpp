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
	TextEntity(float x, float y, float scale, std::string message, int fontSize, SDL_Color color, TTF_Font* font);
	void updateText(std::string message);
	TTF_Font* font;
	int size;
	SDL_Color color;
};