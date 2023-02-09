#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector2.hpp"
#include "RenderWindow.hpp"
#include "Utils.hpp"


class Entity
{
public:
    Entity(float x, float y, float scale, SDL_Texture* tex, int sortOrder);
    Vector2 pos;
    bool enabled;
    float scale;
    double angle = 0;
    //higher sort order entities will be updated after lower sort order entities
    int sortOrder;
    //rect determining dimensions and screen space position of texture being rendered to the screen
    SDL_Rect currentFrame;
    //texture to be rendered to the window
    SDL_Texture* tex;

    /// <summary>
    /// render entity to window
    /// </summary>
    virtual void render();

    /// <summary>
    /// called every frame to make neccessary changes to state of entity
    /// </summary>
    virtual void update();

    /// <summary>
    /// called before update to do any required initialization
    /// </summary>
    virtual void init();
    Entity();
    virtual ~Entity();
};