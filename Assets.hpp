#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_TTF.h>
#include "RenderWindow.hpp"

class Assets
{
public:
	Assets(const Assets&) = delete;
	static Assets& Instance();
	void loadAssets();
	void loadImages();
	void loadFonts();
	void closeFonts();
	SDL_Texture* img_Test;
	SDL_Texture* img_Background;
	SDL_Texture* img_ScrollArea;
	SDL_Texture* img_ScrollBarSmall;
	SDL_Texture* img_ScrollBarMed;
	SDL_Texture* img_ScrollBarLarge;
	SDL_Texture* img_OverList;

	TTF_Font* font_Test;

private:
	Assets();
};