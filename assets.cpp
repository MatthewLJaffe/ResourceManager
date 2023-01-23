#include "Assets.hpp"

Assets& Assets::Instance()
{
    static Assets assets;
    return assets;
}

void Assets::loadAssets()
{
    loadImages();
    loadFonts();
}

void Assets::loadImages()
{
    RenderWindow &rw = RenderWindow::Instance();
    img_Test = rw.loadTexture("Assets/images/TestSprite.png");
    img_Background = rw.loadTexture("Assets/images/ResourceManagerBackground.png");
    img_GraphView = rw.loadTexture("Assets/images/GraphView.png");
    img_ListView = rw.loadTexture("Assets/images/ListView.png");
    img_GraphBorders = rw.loadTexture("Assets/images/GraphBorders.png");
    img_ListBorders = rw.loadTexture("Assets/images/OverList.png");
    img_ScrollArea = rw.loadTexture("Assets/images/ScrollBarArea.png");
    img_ScrollBarSmall = rw.loadTexture("Assets/images/ScrollBar.png");
    img_ScrollBarMed = rw.loadTexture("Assets/images/ScrollBarMedium.png");
    img_ScrollBarLarge = rw.loadTexture("Assets/images/ScrollBarLarge.png");
    img_ArrowRight = rw.loadTexture("Assets/images/ArrowRight.png");
    img_ArrowBottomLeft = rw.loadTexture("Assets/images/ArrowBottomLeft.png");
    img_ArrowBottomRight = rw.loadTexture("Assets/images/ArrowBottomRight.png");
    img_ArrowDown = rw.loadTexture("Assets/images/ArrowDown.png");
    img_ArrowLeft = rw.loadTexture("Assets/images/ArrowLeft.png");
    img_ArrowTopLeft = rw.loadTexture("Assets/images/ArrowTopLeft.png");
    img_ArrowTopRight = rw.loadTexture("Assets/images/ArrowTopRight.png");
    img_ArrowUp = rw.loadTexture("Assets/images/ArrowUp.png");
    img_circleNode = rw.loadTexture("Assets/images/ResourceNodeCircle.png");
    img_selectedCircleNode = rw.loadTexture("Assets/images/SelectedResourceNodeCircle.png");
    img_craftButton = rw.loadTexture("Assets/images/CraftButton1.png");	
    img_craftButtonPressed = rw.loadTexture("Assets/images/CraftButton2.png");
    img_StartMenuBackground = rw.loadTexture("Assets/images/StartMenuBackground.png");
    img_StartMenuButton = rw.loadTexture("Assets/images/StartButton1.png");
    img_StartMenuButtonPressed = rw.loadTexture("Assets/images/StartButton2.png");
    img_ExitButton = rw.loadTexture("Assets/images/ExitButton1.png");
    img_ExitButtonPressed = rw.loadTexture("Assets/images/ExitButton2.png");
    img_GameSky = rw.loadTexture("Assets/images/GameSky.png");
    img_GameBackground = rw.loadTexture("Assets/images/GameBackground.png");
    img_GameForeground = rw.loadTexture("Assets/images/GameForeground.png");
    img_FloorTile = rw.loadTexture("Assets/images/FloorTile.png");
    img_Ore = rw.loadTexture("Assets/images/Ore.png");
    img_PlayerRight = rw.loadTexture("Assets/images/characters/WelderRight.png");
    img_PlayerLeft = rw.loadTexture("Assets/images/characters/WelderLeft.png");
    std::string fileEnd(".png");
    for (int i = 1; i <= 8; i++)
    {
        std::string playerWalkLeftPath = "Assets/images/characters/WelderWalkLeft" + std::to_string(i) + ".png";
        std::string playerWalkRightPath = "Assets/images/characters/WelderWalkRight" + std::to_string(i) + ".png";
        img_PlayerWalkLeft[i-1] = rw.loadTexture(playerWalkLeftPath.c_str());
        img_PlayerWalkRight[i-1] = rw.loadTexture(playerWalkRightPath.c_str());
        std::string enemyWalkLeftPath = "Assets/images/characters/AlienWalkLeft" + std::to_string(i) + ".png";
        std::string enemyWalkRightPath = "Assets/images/characters/AlienWalkRight" + std::to_string(i) + ".png";
        img_EnemyWalkLeft[i-1] = rw.loadTexture(enemyWalkLeftPath.c_str());
        img_EnemyWalkRight[i-1] = rw.loadTexture(enemyWalkRightPath.c_str());
    }
}

void Assets::loadFonts()
{
    font_Test = TTF_OpenFont("Assets/fonts/pixel-bit-advanced.ttf", 30);
    font_Body = TTF_OpenFont("Assets/fonts/TinyPixie2.ttf", 30);
}

void Assets::closeFonts()
{
    TTF_CloseFont(font_Test);
}

Assets::Assets() {}
