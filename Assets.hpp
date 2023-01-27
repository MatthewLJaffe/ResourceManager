#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_TTF.h>
#include "RenderWindow.hpp"
#include <string>
#include <vector>

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
	std::vector<SDL_Texture*> imgs_PlayerWalkLeft;
	std::vector<SDL_Texture*> imgs_PlayerWalkRight;
	std::vector<SDL_Texture*> imgs_EnemyWalkLeft;
	std::vector<SDL_Texture*> imgs_EnemyWalkRight;
	SDL_Texture* img_PlayerRight;
	SDL_Texture* img_PlayerLeft;
	SDL_Texture* img_InventoryUI;
	SDL_Texture* img_Yellow;
	SDL_Texture* img_White;
	SDL_Texture* img_SpikesUI;
	SDL_Texture* img_GunUI;
	SDL_Texture* img_TurretUI;
	SDL_Texture* img_BombUI;
	SDL_Texture* img_HandCannonUI;
	SDL_Texture* img_CannonUI;
	std::vector<SDL_Texture*> imgs_bulletDestroyLeft;
	std::vector<SDL_Texture*> imgs_bulletDestroyRight;
	std::vector<SDL_Texture*> imgs_missileDestroyLeft;
	std::vector<SDL_Texture*> imgs_missileDestroyRight;
	std::vector<SDL_Texture*> imgs_turretRight;
	std::vector<SDL_Texture*> imgs_turretLeft;
	SDL_Texture* img_TransparentTurretRight;
	SDL_Texture* img_TransparentTurretLeft;
	SDL_Texture* img_ScrapPileTransparent;
	SDL_Texture* img_ScrapPile;
	SDL_Texture* img_GunPowder;
	SDL_Texture* img_BombPreview;
	std::vector<SDL_Texture*> imgs_bomb;
	std::vector<SDL_Texture*> imgs_CannonRight;
	std::vector<SDL_Texture*> imgs_CannonLeft;
	SDL_Texture* img_CannonPreviewRight;
	SDL_Texture* img_CannonPreviewLeft;
	std::vector<SDL_Texture*> imgs_AlienWalkLeftDamage;
	std::vector<SDL_Texture*> imgs_AlienWalkRightDamage;
	std::vector<SDL_Texture*> imgs_AlienAttackRightDamage;
	std::vector<SDL_Texture*> imgs_AlienAttackLeftDamage;
	std::vector<SDL_Texture*> imgs_AlienAttackLeft;
	std::vector<SDL_Texture*> imgs_AlienAttackRight;
	std::vector<SDL_Texture*> imgs_AlienDieLeft;
	std::vector<SDL_Texture*> imgs_AlienDieRight;
	std::vector<SDL_Texture*> imgs_PlayerDieLeft;
	std::vector<SDL_Texture*> imgs_PlayerDieRight;
	std::vector<SDL_Texture*> imgs_MissileTurretDestroyLeft;
	std::vector<SDL_Texture*> imgs_MissileTurretDestroyRight;
	std::vector<SDL_Texture*> imgs_TurretDestroyRight;
	std::vector<SDL_Texture*> imgs_TurretDestroyLeft;
	SDL_Texture* img_GameOverBackground;
	SDL_Texture* img_ContinueButton;
	SDL_Texture* img_ContinueButtonPressed;
	TTF_Font* font_Test;
	TTF_Font* font_Body;

private:
	Assets();
};