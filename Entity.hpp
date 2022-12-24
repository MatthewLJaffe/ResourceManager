#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector2.hpp"

class Entity
{
public:
    Entity(float x, float y, SDL_Texture* tex);
    Entity(SDL_Rect rect, SDL_Texture* tex);
    ~Entity();
    Vector2* pos;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
    void init();
private:

};