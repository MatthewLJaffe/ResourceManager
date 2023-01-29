#include "TextEntity.hpp"
TextEntity::TextEntity(float x, float y, float scale, std::string message, int fontSize, SDL_Color color, TTF_Font* font, size_t maxChars, int sortOrder)
{
    this->maxChars = maxChars;
    this->sortOrder = sortOrder;
    this->size = fontSize;
    this->color = color;
    this->font = font;
	this->pos = new Vector2(x, y);
    this->scale = scale;
    this->text = message;
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
    this->text = message;
    if (message.size() > maxChars) {
        message = message.substr(0, maxChars - 3) + "...";
    }
    TTF_SetFontSize(font, size);
    SDL_Surface* textSurf = TTF_RenderText_Solid(font, message.c_str(), color);
    SDL_DestroyTexture(tex);
    tex = RenderWindow::Instance().createFontTexture(textSurf);
    currentFrame = { 0, 0, textSurf->w, textSurf->h };
    SDL_FreeSurface(textSurf);
}

TextEntity::TextEntity() {}

TextEntity::~TextEntity() 
{
    SDL_DestroyTexture(this->tex);
}