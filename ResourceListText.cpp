#include "ResourceListText.hpp"

float ResourceListText::verticalOffset = 0;

ResourceListText::ResourceListText(float x, float y, float scale, std::string message, int fontSize, SDL_Color color, TTF_Font* font, int maxChars, int sortOrder) : 
    TextEntity(x,y,scale,message,fontSize, color, font, maxChars, sortOrder)
{
    if (message.size() > maxChars && message.find(' ') != std::string::npos)
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

void ResourceListText::updateText(std::string message)
{
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

void ResourceListText::render()
{
    if (!enabled) return;
    SDL_Rect destRect = { pos->x * scale, (pos->y + verticalOffset) * scale, currentFrame.w * scale, currentFrame.h * scale };
    RenderWindow::Instance().render(tex, currentFrame, destRect, angle);
}
