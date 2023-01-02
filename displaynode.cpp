#include "DisplayNode.hpp"

OutgoingArrow::OutgoingArrow(DisplayNode* target, Vector2* targetOffset, Vector2* originOffset, ArrowEntity* arrow)
{
	this->target = target;
	this->targetOffset = targetOffset;
	this->originOffset = originOffset;
	this->arrow = arrow;
}

DisplayNode::DisplayNode(float x, float y, float scale, SDL_Texture* tex, int sortOrder, std::string name)
{
    this->sortOrder = sortOrder;
    this->pos = new Vector2(x, y);
    this->tex = tex;
    this->scale = scale;
    currentFrame.x = 0;
    currentFrame.y = 0;
    this->name = name;
    SDL_QueryTexture(this->tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
    TTF_SetFontSize(Assets::Instance().font_Body, 10 + 60 / (float(name.size())));
    SDL_Surface* textSurf = TTF_RenderText_Solid(Assets::Instance().font_Body, name.c_str(), {255,255,255});
    textImg = RenderWindow::Instance().createFontTexture(textSurf);
    SDL_FreeSurface(textSurf);
    enabled = true;
}

void DisplayNode::render()
{
    if (!enabled) return;
    RenderWindow::Instance().render(tex, currentFrame, { int(pos->x * scale), int(pos->y * scale), int(currentFrame.w * scale), int(currentFrame.h * scale) }, 0);
    int textW, textH;
    SDL_QueryTexture(this->textImg, NULL, NULL, &textW, &textH);
    Vector2 textPos(pos->x, pos->y);
    textPos.x += (currentFrame.w / 2 - textW/scale / 2);
    textPos.y += (currentFrame.h / 2 - textH/scale / 2);
    SDL_Rect textRect;
    textRect.x = 0;
    textRect.y = 0;
    textRect.w = textW;
    textRect.h = textH;
    RenderWindow::Instance().render(textImg, textRect, { int(textPos.x * scale), int(textPos.y * scale), int(textW), int(textH) }, 0);
}

void DisplayNode::update()
{
    if (!enabled) return;
    for (size_t i = 0; i < outgoingArrows.size(); i++)
    {
        outgoingArrows[i]->arrow->from->x = pos->x + 24 + outgoingArrows[i]->originOffset->x;
        outgoingArrows[i]->arrow->from->y = pos->y+ 24 + outgoingArrows[i]->originOffset->y;
        outgoingArrows[i]->arrow->to->x = outgoingArrows[i]->targetOffset->x + outgoingArrows[i]->target->pos->x + 24;
        outgoingArrows[i]->arrow->to->y = outgoingArrows[i]->targetOffset->y + outgoingArrows[i]->target->pos->y + 24;
    }
}