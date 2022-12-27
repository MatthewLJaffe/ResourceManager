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
	void loadAssets(RenderWindow* rw);
	void loadImages(RenderWindow* rw);
	void loadFonts();
	void closeFonts();
	SDL_Texture* img_Test;
	SDL_Texture* img_Background;
	TTF_Font* font_Test;

private:
	Assets();
};