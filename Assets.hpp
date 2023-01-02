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
	SDL_Texture* img_GraphView;
	SDL_Texture* img_OverList;
	SDL_Texture* img_ScrollArea;
	SDL_Texture* img_ScrollBarSmall;
	SDL_Texture* img_ScrollBarMed;
	SDL_Texture* img_ScrollBarLarge;
	SDL_Texture* img_ArrowRight;
	SDL_Texture* img_ArrowTopRight;
	SDL_Texture* img_ArrowUp;
	SDL_Texture* img_ArrowTopLeft;
	SDL_Texture* img_ArrowLeft;
	SDL_Texture* img_ArrowBottomLeft;
	SDL_Texture* img_ArrowDown;
	SDL_Texture* img_ArrowBottomRight;
	SDL_Texture* img_circleNode;
	TTF_Font* font_Test;
	TTF_Font* font_Body;

private:
	Assets();
};