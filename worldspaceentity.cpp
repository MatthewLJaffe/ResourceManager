#include "WorldSpaceEntity.hpp"

WorldSpaceEntity::WorldSpaceEntity(float x, float y, float scale, SDL_Texture* tex, int sortOrder) : Entity(x, y, scale, tex, sortOrder)
{
    this->originalScale = scale;
}

void WorldSpaceEntity::render()
{
    if (!enabled) return;
    Vector2 renderPos = (pos + transformState.translation + screenCenterOffset) * scale;
    renderPos.x -= currentFrame.w * scale / 2;
    renderPos.y -= currentFrame.h * scale / 2;
    SDL_Rect destRect = { utils::roundFloat(renderPos.x), utils::roundFloat(renderPos.y), utils::roundFloat(currentFrame.w * scale), utils::roundFloat(currentFrame.h * scale) };
    RenderWindow::Instance().render(tex, currentFrame, destRect, angle);
}

void WorldSpaceEntity::updateTransformState()
{
    Transformable::updateTransformState();
    scale = transformState.scale.x * originalScale;
}

void WorldSpaceEntity::update()
{
    updateTransformState();
}