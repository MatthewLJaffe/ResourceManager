#include "TextEntity.hpp"

TextEntity::TextEntity(float x, float y, std::string text, int size, TTF_Font* font, SDL_Color color, RenderWindow* renderWindow)
{
	this->pos = new Vector2(x, y);
    SDL_Surface* textSurf = TTF_RenderText_Solid(font, text.c_str(), color);
    tex = renderWindow->createFontTexture(textSurf);
    this->currentFrame = { 0, 0, textSurf->w, textSurf->h };
    SDL_FreeSurface(textSurf);
}