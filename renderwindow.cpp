#include "RenderWindow.hpp"

RenderWindow& RenderWindow::Instance()
{
    static RenderWindow renderWindow;
    return renderWindow;
}

RenderWindow::RenderWindow()
{
    window = SDL_CreateWindow("Resource Manager", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

    if (window == NULL)
        std::cout << "Window failed to init. Error " << SDL_GetError() << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);
    if (texture == NULL)
        std::cout << "Failed to load texture " << SDL_GetError() << std::endl;
    return texture;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect)
{
    SDL_RenderCopy(renderer, tex, &srcRect, &destRect);
}


SDL_Texture* RenderWindow::createFontTexture(SDL_Surface* textSurf)
{
    return SDL_CreateTextureFromSurface(renderer, textSurf);
}


void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}