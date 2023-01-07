#include "TextEntity.hpp"
TextEntity::TextEntity(float x, float y, float scale, std::string message, int fontSize, SDL_Color color, TTF_Font* font, int maxChars, int sortOrder)
{
    this->maxChars = maxChars;
    this->sortOrder = sortOrder;
    this->size = fontSize;
    this->color = color;
    this->font = font;
	this->pos = new Vector2(x, y);
    this->scale = scale;
    TTF_SetFontSize(font, fontSize);
    if (message.size() > maxChars) {
        message = message.substr(0, maxChars - 3) + "...";
    }
    SDL_Surface* textSurf = TTF_RenderText_Solid(font, message.c_str(), color);
    tex = RenderWindow::Instance().createFontTexture(textSurf);
    currentFrame = { 0, 0, textSurf->w, textSurf->h };
    SDL_FreeSurface(textSurf);
    enabled = true;
}

void TextEntity::updateText(std::string message)
{
    if (message.size() > maxChars) {
        message = message.substr(0, maxChars - 3) + "...";
    }
    TTF_SetFontSize(font, size);
    SDL_Surface* textSurf = TTF_RenderText_Solid(font, message.c_str(), color);
    tex = RenderWindow::Instance().createFontTexture(textSurf);
    currentFrame = { 0, 0, textSurf->w, textSurf->h };
    SDL_FreeSurface(textSurf);
}

TextEntity::TextEntity() {}