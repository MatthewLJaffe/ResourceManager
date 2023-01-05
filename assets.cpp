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
