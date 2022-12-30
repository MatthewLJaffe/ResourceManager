#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class RenderWindow
{
    public:
        RenderWindow(const RenderWindow&) = delete;
        static RenderWindow& Instance();
        SDL_Texture* loadTexture(const char* filePath);
        void cleanUp();
        void clear();
        void render(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect);
        void display();
        SDL_Texture* createFontTexture(SDL_Surface* textSurf);
    private:
        RenderWindow();
        SDL_Window* window;
        SDL_Renderer* renderer;
};