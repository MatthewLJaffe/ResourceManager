#include "Entity.hpp"

Entity::Entity(float x, float y, float scale, SDL_Texture* tex, int sortOrder)
{
    this->sortOrder = sortOrder;
    this->pos = new Vector2(x, y);
    this->tex = tex;
    this->scale = scale;
    currentFrame.x = 0;
    currentFrame.y = 0;
    SDL_QueryTexture(this->tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
    enabled = true;
    init();
}

Entity::Entity() {}

void Entity::update() { }

void Entity::init() { }

void Entity::render()
{
    if (!enabled) return;
    SDL_Rect destRect = { pos->x * scale, pos->y * scale, currentFrame.w * scale, currentFrame.h * scale };
    RenderWindow::Instance().render(tex, currentFrame, destRect);
}

Entity::~Entity()
{
    delete this->pos;
};
