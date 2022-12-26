#include "Entity.hpp"

Entity::Entity(float x, float y, float scale, SDL_Texture* tex)
{
    this->pos = new Vector2(x, y);
    this->tex = tex;
    this->scale = scale;
    currentFrame.x = 0;
    currentFrame.y = 0;
    SDL_QueryTexture(this->tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
    init();
}

Entity::Entity() {}

void Entity::update()
{
    if (!enabled) return;
    
}

void Entity::init()
{

}

Entity::Entity() {}

void update()
{

}

Entity::~Entity()
{
    delete this->pos;
};
