#include "ResourceListText.hpp"

float ResourceListText::verticalOffset = 0;

ResourceListText::ResourceListText(float x, float y, float scale, std::string message, int fontSize, SDL_Color color, TTF_Font* font, int sortOrder)
{
    this->sortOrder = sortOrder;
    this->size = fontSize;
    this->color = color;
    this->font = font;
    this->pos = new Vector2(x, y);
    this->scale = scale;
    TTF_SetFontSize(font, fontSize);
    SDL_Surface* textSurf = TTF_RenderText_Solid(font, message.c_str(), color);
    tex = RenderWindow::Instance().createFontTexture(textSurf);
    currentFrame = { 0, 0, textSurf->w, textSurf->h };
    SDL_FreeSurface(textSurf);
    enabled = true;
}

void ResourceListText::render()
{
    if (!enabled) return;
    SDL_Rect destRect = { pos->x * scale, (pos->y + verticalOffset) * scale, currentFrame.w * scale, currentFrame.h * scale };
    RenderWindow::Instance().render(tex, currentFrame, destRect);
}

