#include "Assets.hpp"

Assets& Assets::Instance()
{
    static Assets assets;
    return assets;
}

void Assets::loadAssets(RenderWindow* renderer)
{
    loadImages(renderer);
    loadFonts();
}

void Assets::loadFonts()
{
    font_Test = TTF_OpenFont("Assets/fonts/pixel-bit-advanced.ttf", 30);
}

void Assets::loadImages(RenderWindow* renderWindow)
{
    img_Test = renderWindow->loadTexture("Assets/images/TestSprite.png");
}

Assets::Assets() {}
