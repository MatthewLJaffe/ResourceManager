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
    img_Background = rw.loadTexture("Assets/images/ResourceManagerUI.png");
    img_ScrollArea = rw.loadTexture("Assets/images/ScrollBarArea.png");
    img_ScrollBarSmall = rw.loadTexture("Assets/images/ScrollBar.png");
    img_OverList = rw.loadTexture("Assets/images/OverList.png");
    img_ScrollBarMed = rw.loadTexture("Assets/images/ScrollBarMedium.png");;
    img_ScrollBarLarge = rw.loadTexture("Assets/images/ScrollBarLarge.png");;
}

void Assets::loadFonts()
{
    font_Test = TTF_OpenFont("Assets/fonts/pixel-bit-advanced.ttf", 30);
}

void Assets::closeFonts()
{
    TTF_CloseFont(font_Test);
}

Assets::Assets() {}
