#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector2.hpp"
#include "RenderWindow.hpp"

class Entity
{
public:
    Entity(float x, float y, SDL_Texture* tex);
    Entity(SDL_Rect rect, SDL_Texture* tex);
    Entity();
    ~Entity();
    void update();
    Vector2* pos;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
    void init();
private:

};