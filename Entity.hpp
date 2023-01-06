#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector2.hpp"
#include "RenderWindow.hpp"


class Entity
{
public:
    Entity(float x, float y, float scale, SDL_Texture* tex, int sortOrder);
    virtual ~Entity();
    Vector2* pos;
    bool enabled;
    float scale;
    double angle = 0;
    int sortOrder;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
    virtual void render();
    virtual void update();
    virtual void init();
    Entity();
private:

};