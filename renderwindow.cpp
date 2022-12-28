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

void RenderWindow::render(Entity& entity)
{
    SDL_Rect src;
    src.x = entity.currentFrame.x;
    src.y = entity.currentFrame.y;
    src.w = entity.currentFrame.w;
    src.h = entity.currentFrame.h;

    SDL_Rect dst;
    dst.x = entity.pos->x * entity.scale;
    dst.y = entity.pos->y * entity.scale;
    dst.w = src.w * entity.scale;
    dst.h = src.h * entity.scale;
    SDL_RenderCopy(renderer, entity.tex, &src, &dst);
}

void RenderWindow::renderUnscaled(Entity& entity)
{
    SDL_Rect dst;
    dst.x = entity.pos->x;
    dst.y = entity.pos->y;
    dst.w = entity.currentFrame.w;
    dst.h = entity.currentFrame.h;
    SDL_RenderCopy(renderer, entity.tex, NULL, &dst);

}


SDL_Texture* RenderWindow::createFontTexture(SDL_Surface* textSurf)
{
    return SDL_CreateTextureFromSurface(renderer, textSurf);
}


void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}