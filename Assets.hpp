#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_TTF.h>
#include "RenderWindow.hpp"
#include <string>

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
	SDL_Texture* img_GraphBorders;
	SDL_Texture* img_GraphView;
	SDL_Texture* img_ListView;
	SDL_Texture* img_ListBorders;
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
	SDL_Texture* img_selectedCircleNode;
	SDL_Texture* img_craftButton;
	SDL_Texture* img_craftButtonPressed;
	SDL_Texture* img_StartMenuBackground;
	SDL_Texture* img_StartMenuButton;
	SDL_Texture* img_StartMenuButtonPressed;
	SDL_Texture* img_ExitButton;
	SDL_Texture* img_ExitButtonPressed;
	SDL_Texture* img_GameSky;
	SDL_Texture* img_GameBackground;
	SDL_Texture* img_GameForeground;
	SDL_Texture* img_FloorTile;
	SDL_Texture* img_Ore;
	SDL_Texture* img_PlayerWalkLeft[8];
	SDL_Texture* img_PlayerWalkRight[8];
	SDL_Texture* img_EnemyWalkLeft[8];
	SDL_Texture* img_EnemyWalkRight[8];
	SDL_Texture* img_PlayerRight;
	SDL_Texture* img_PlayerLeft;
	TTF_Font* font_Test;
	TTF_Font* font_Body;

private:
	Assets();
};