#include "ResourceListText.hpp"

float ResourceListText::verticalOffset = 0;

ResourceListText::ResourceListText(float x, float y, float scale, std::string message, std::string name, int fontSize, SDL_Color color, TTF_Font* font, int maxChars, int sortOrder, bool requirment, bool selected) : 
    TextEntity(x,y,scale,message,fontSize, color, font, maxChars, sortOrder)
{
    this->requirment = requirment;
    this->selected = selected;
    this->name = name;
}

void ResourceListText::updateText(std::string message)
{
    TTF_SetFontSize(font, size);
    if (message.size() > this->maxChars && message.find(' ') != std::string::npos)
    {
        int spaceIdx = message.find(' ');
        std::string beforeSpace = message.substr(0, spaceIdx);
        std::string afterSpace = message.substr(spaceIdx, message.size() - spaceIdx);
        int newBeforeSize = beforeSpace.size() + (maxChars - message.size()) - 3;
        if (newBeforeSize <= 0)
        {
            std::cout << "maxChars not obtainable for list entry " << message << std::endl;
            return;
        }
        message = beforeSpace.substr(0, newBeforeSize) + "..." + afterSpace;
    }
    SDL_Surface* textSurf = TTF_RenderText_Solid(font, message.c_str(), color);
    tex = RenderWindow::Instance().createFontTexture(textSurf);
    currentFrame = { 0, 0, textSurf->w, textSurf->h };
    SDL_FreeSurface(textSurf);
    enabled = true;
}

void ResourceListText::updateColor(SDL_Color color)
{
    TTF_SetFontSize(font, size);
    SDL_Surface* textSurf = TTF_RenderText_Solid(font, text.c_str(), color);
    tex = RenderWindow::Instance().createFontTexture(textSurf);
    currentFrame = { 0, 0, textSurf->w, textSurf->h };
    SDL_FreeSurface(textSurf);
}

void ResourceListText::render()
{
    if (!enabled) return;
    SDL_Rect destRect = { utils::roundFloat(pos.x * scale), utils::roundFloat((pos.y + verticalOffset) * scale), utils::roundFloat(currentFrame.w * scale), utils::roundFloat(currentFrame.h * scale) };
    RenderWindow::Instance().render(tex, currentFrame, destRect, angle);
}
