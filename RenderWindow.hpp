#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>


class RenderWindow
{
    public:
        RenderWindow(const RenderWindow&) = delete;
        //height of window in pixels
        static const int WIDTH = 1280;
        //width of window in pixels
        static const int HEIGHT = 720;
        static RenderWindow& Instance();
        SDL_Texture* loadTexture(const char* filePath);
        /// <summary>
        /// destroys created textures renderer and window
        /// </summary>
        void cleanUp();
        /// <summary>
        /// clears the current frame
        /// </summary>
        void clear();
        /// <summary>
        /// used to render a texture to the window
        /// </summary>
        /// <param name="tex">texture to render</param>
        /// <param name="srcRect">dimensions and position of source image</param>
        /// <param name="destRect">dimensions and position of destination image</param>
        /// <param name="angle">angle to rotate image</param>
        void render(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect, double angle);
        void drawLine(int x1, int y1, int x2, int y2);
        /// <summary>
        /// displays the current frame
        /// </summary>
        void display();
        /// <summary>
        /// sets scale to render at
        /// </summary>
        /// <param name="x">x scale </param>
        /// <param name="y">y scale</param>
        void setScale(float x, float y);
        /// <summary>
        /// creates texture from a font SDL_Surface*
        /// </summary>
        /// <param name="textSurf">font surface to create texture from</param>
        /// <returns>texture created</returns>
        SDL_Texture* createFontTexture(SDL_Surface* textSurf);
    private:
        RenderWindow();
        std::vector<SDL_Texture*> textures;
        SDL_Window* window;
        SDL_Renderer* renderer;
};