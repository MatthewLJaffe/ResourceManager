#pragma once
#include "TextEntity.hpp"

class ResourceListText :public  TextEntity
{
public:
	ResourceListText(float x, float y, float scale, std::string message, std::string name, int fontSize, SDL_Color color, TTF_Font* font, int maxChars, int sortOrder, bool requirement, bool selected);
	static float verticalOffset;
	void render() override;
	void updateText(std::string message);
	std::string name;
	void updateColor(SDL_Color color);
	bool requirment;
	bool selected;
};