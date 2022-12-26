#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Entity.hpp"


class RenderWindow
{
    public:
        RenderWindow(const char* title, int width, int height);
        SDL_Texture* loadTexture(const char* filePath);
        void cleanUp();
        void clear();
        void render(Entity& tex);
        void renderUnscaled(Entity& entity);
        void display();
        SDL_Texture* createFontTexture(SDL_Surface* textSurf);
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};