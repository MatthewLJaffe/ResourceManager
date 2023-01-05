#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class RenderWindow
{
    public:
        RenderWindow(const RenderWindow&) = delete;
        static const int WIDTH = 1280;
        static const int HEIGHT = 720;
        static RenderWindow& Instance();
        SDL_Texture* loadTexture(const char* filePath);
        void cleanUp();
        void clear();
        void render(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect, double angle);
        void drawLine(int x1, int y1, int x2, int y2);
        void display();
        void setScale(float x, float y);
        SDL_Texture* createFontTexture(SDL_Surface* textSurf);
    private:
        RenderWindow();
        SDL_Window* window;
        SDL_Renderer* renderer;
};