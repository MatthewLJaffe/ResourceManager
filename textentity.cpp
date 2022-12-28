#include "TextEntity.hpp"
TextEntity::TextEntity(float x, float y, float scale, std::string message, int fontSize, SDL_Color color, TTF_Font* font)
{
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
}

void TextEntity::updateText(std::string message)
{
    TTF_SetFontSize(font, size);
    SDL_Surface* textSurf = TTF_RenderText_Solid(font, message.c_str(), color);
    tex = RenderWindow::Instance().createFontTexture(textSurf);
    currentFrame = { 0, 0, textSurf->w, textSurf->h };
    SDL_FreeSurface(textSurf);
}
