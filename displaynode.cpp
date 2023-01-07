#include "DisplayNode.hpp"

OutgoingArrow::OutgoingArrow(std::string target, ArrowEntity* arrow)
{
	this->target = target;
	this->arrow = arrow;
}

DisplayNode::DisplayNode(float x, float y, float scale, SDL_Texture* tex, int sortOrder, std::string name, int maxChars)
{
    this->sortOrder = sortOrder;
    this->scale = scale;
    this->pos = new Vector2(x, y);
    this->tex = tex;
    currentFrame.x = 0;
    currentFrame.y = 0;
    this->name = name;
    if (this->name.size() > maxChars)
        this->displayName = this->name.substr(0, maxChars - 3) + "...";
    else
        this->displayName = this->name;
    SDL_QueryTexture(this->tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
    TTF_SetFontSize(Assets::Instance().font_Body, 20);
    SDL_Surface* textSurf = TTF_RenderText_Solid(Assets::Instance().font_Body, displayName.c_str(), {255,255,255});
    textImg = RenderWindow::Instance().createFontTexture(textSurf);
    SDL_FreeSurface(textSurf);
    enabled = true;
}

void DisplayNode::render()
{
    if (!enabled) return;
    RenderWindow::Instance().render(tex, currentFrame, { int(pos->x * scale + viewportCenter.x * 4), int(pos->y * scale + viewportCenter.y * 4), int(currentFrame.w * scale), int(currentFrame.h * scale) }, 0);
    int textW, textH;
    SDL_QueryTexture(this->textImg, NULL, NULL, &textW, &textH);
    Vector2 textPos(pos->x, pos->y);
    textPos.x += (currentFrame.w / 2 - textW/8);
    textPos.y += (currentFrame.h / 2 - textH/8);
    SDL_Rect textRect;
    textRect.x = 0;
    textRect.y = 0;
    textRect.w = textW;
    textRect.h = textH;
    RenderWindow::Instance().render(textImg, textRect, { int(textPos.x * scale + viewportCenter.x * 4), int(textPos.y * scale + viewportCenter.y * 4), int(textW * (scale / 4)), int(textH * (scale/4)) }, 0);
}

void DisplayNode::updateTransformState()
{
    lastTransfromState = transformState;
    transformState = GameTransformer::Instance().getTransformState();
    this->scale = 4.0f * transformState.scale.x;
    transformState.translation /= scale;
    *this->pos -= lastTransfromState.translation * lastTransfromState.scale / transformState.scale;
    *this->pos += transformState.translation;
}

void DisplayNode::update()
{
    if (!enabled) return;
    updateTransformState();
    for (size_t i = 0; i < outgoingArrows.size(); i++)
    {
        //if resource was erased remove outgoing arrow to it since it no longer exists
        if (ResourceManager::Instance().displayMap.count(outgoingArrows[i]->target) == 0)
        {
            Game::Instance().RemoveEntity(outgoingArrows[i]->arrow);
            delete outgoingArrows[i]->arrow;
            OutgoingArrow* outgoingArrow = outgoingArrows[i];
            outgoingArrows.erase(outgoingArrows.begin() + i);
            delete outgoingArrow;
            i--;
            continue;
        }
        //if resource was deleted disable outgoing arrow since resource still exists in graph
        if (!ResourceManager::Instance().displayMap[outgoingArrows[i]->target]->enabled)
        {
            outgoingArrows[i]->arrow->enabled = false;
            continue;
        }
        outgoingArrows[i]->arrow->enabled = true;
        DisplayNode* target = ResourceManager::Instance().displayMap[outgoingArrows[i]->target];
        Vector2 dir = target->getCenterPos() - getCenterPos();
        dir.normalize();
        *outgoingArrows[i]->arrow->from = getCenterPos() + dir * size / 2;
        *outgoingArrows[i]->arrow->to = target->getCenterPos() - dir * size / 2;
    }
}

Vector2 DisplayNode::getScreenPos(Vector2 centerPos)
{
    return centerPos - size / 2;
}

Vector2 DisplayNode::getCenterPos()
{
    return *pos + size / 2;
}

Vector2 DisplayNode::screenSpaceSize()
{
    return size * scale;
}

DisplayNode::~DisplayNode()
{
    for (int i = 0; i < outgoingArrows.size(); i++)
        delete outgoingArrows[i];
}

