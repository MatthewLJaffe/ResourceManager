#include "Assets.hpp"

Assets& Assets::Instance()
{
    static Assets assets;
    return assets;
}

void Assets::loadAssets(RenderWindow* rw)
{
    loadImages(rw);
    loadFonts();
}

void Assets::loadImages(RenderWindow* rw)
{
    img_Test = rw->loadTexture("Assets/images/TestSprite.png");
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
