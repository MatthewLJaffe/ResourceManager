#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector2.hpp"


class Entity
{
public:
    Entity(float x, float y, float scale, SDL_Texture* tex);
    ~Entity();
    Vector2* pos;
    bool enabled;
    float scale;
    void update();
    SDL_Rect currentFrame;
    SDL_Texture* tex;
    void init();
    Entity();
private:

};