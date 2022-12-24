#include "Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity(float x, float y, SDL_Texture* tex)
{
    this->pos = new Vector2(x, y);
    this->tex = tex;
    currentFrame.x = 0;
    currentFrame.y = 0;
    SDL_QueryTexture(this->tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}

Entity::~Entity()
{
    delete this->pos;
};