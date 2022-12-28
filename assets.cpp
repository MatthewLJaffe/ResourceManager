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
    img_Test = RenderWindow::Instance().loadTexture("Assets/images/TestSprite.png");
    img_Background = RenderWindow::Instance().loadTexture("Assets/images/ResourceManagerUI.png");
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
