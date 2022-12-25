#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "RenderWindow.hpp"



class Assets
{
public:
	Assets(const Assets&) = delete;
	static Assets& Instance();
	void loadAssets(RenderWindow*);
	void loadImages(RenderWindow*);
	void loadFonts();
	SDL_Texture* img_Test;
	TTF_Font* font_Test;

private:
	Assets();
};