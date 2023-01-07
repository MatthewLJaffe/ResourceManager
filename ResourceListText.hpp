#pragma once
#include "TextEntity.hpp"

class ResourceListText :public  TextEntity
{
public:
	ResourceListText(float x, float y, float scale, std::string message, int fontSize, SDL_Color color, TTF_Font* font, int maxChars, int sortOrder);
	static float verticalOffset;
	void render() override;
	void updateText(std::string message);
};