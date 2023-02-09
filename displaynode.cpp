#include "DisplayNode.hpp"


OutgoingArrow::OutgoingArrow(std::string target, ArrowEntity* arrow)
{
	this->target = target;
	this->arrow = arrow;
}

DisplayNode::DisplayNode(float x, float y, float scale, SDL_Texture* tex, int sortOrder, std::string name, int displayAmount, size_t maxChars)
{
    this->sortOrder = sortOrder;
    this->scale = defaultScale;
    this->pos = Vector2(x, y);
    this->tex = tex;
    currentFrame.x = 0;
    currentFrame.y = 0;
    this->name = name;
    this->displayAmount = displayAmount;
    if (this->name.size() > maxChars)
        this->displayName = this->name.substr(0, maxChars - 3) + "...";
    else
        this->displayName = this->name;
    SDL_QueryTexture(this->tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
    TTF_SetFontSize(Assets::Instance().font_Body, 20);
    SDL_Surface* textSurf = TTF_RenderText_Solid(Assets::Instance().font_Body, displayName.c_str(), {255,255,255});
    nameTextImg = RenderWindow::Instance().createFontTexture(textSurf);
    SDL_FreeSurface(textSurf);
    textSurf = TTF_RenderText_Solid(Assets::Instance().font_Body, ("x" + std::to_string(displayAmount)).c_str(), {255,255,255});
    amountTextImg = RenderWindow::Instance().createFontTexture(textSurf);
    SDL_FreeSurface(textSurf);
    textSurf = TTF_RenderText_Solid(Assets::Instance().font_Body, "craft", {255,255,255});
    craftTextImg = RenderWindow::Instance().createFontTexture(textSurf);
    SDL_FreeSurface(textSurf);
    buttonImg = Assets::Instance().img_craftButton;
    buttonDownImg = Assets::Instance().img_craftButtonPressed;
    enabled = true;
    this->buttonState = buttonImg;
}

bool DisplayNode::posInCraftButton(Vector2 pos)
{
    if (!displayCraftButton) return false;
    //converting to world space coordinates
    pos -= viewportCenter;
    pos *= 4 / this->scale;

    if (pos.x > this->pos.x + craftButtonRect.x && pos.x < this->pos.x + craftButtonRect.x + craftButtonRect.w && 
        pos.y > this->pos.y + craftButtonRect.y && pos.y < this->pos.y + craftButtonRect.y + craftButtonRect.h)
    {
        return true;
    }
    return false;
}

void DisplayNode::setDisplayAmount(int newAmount)
{
    displayAmount = newAmount;
    TTF_SetFontSize(Assets::Instance().font_Body, 20);
    SDL_Surface* textSurf = TTF_RenderText_Solid(Assets::Instance().font_Body, ("x" + std::to_string(displayAmount)).c_str(), { 255,255,255 });
    amountTextImg = RenderWindow::Instance().createFontTexture(textSurf);
}


void DisplayNode::renderTextAtVerticalOffset(SDL_Texture* textImg, float yOffset)
{
    int textW, textH;
    SDL_QueryTexture(textImg, NULL, NULL, &textW, &textH);
    Vector2 textPos(pos.x, pos.y);
    textPos.x += (currentFrame.w / 2 - textW / 8);
    textPos.y += (currentFrame.h / 2 - textH / 8);
    textPos.y += yOffset;
    SDL_Rect textRect;
    textRect.x = 0;
    textRect.y = 0;
    textRect.w = textW;
    textRect.h = textH;
    RenderWindow::Instance().render(textImg, textRect, { int(textPos.x * scale + viewportCenter.x * 4), int(textPos.y * scale + viewportCenter.y * 4), int(textW * (scale / 4)), int(textH * (scale / 4)) }, 0);
}

void DisplayNode::update()
{
    if (!enabled) return;
    if (displayCraftButton)
    {
        if (InputManager::Instance().getMouseDown() && posInCraftButton(InputManager::Instance().getMousePos() / 4))
        {
            buttonState = buttonDownImg;
        }
        else
        {
            buttonState = buttonImg;
        }
    }
    updateTransformState();
    std::vector<std::string> removedArrows;
    for (auto targetArrow : outgoingArrows)
    {
        //if resource was erased remove outgoing arrow to it since it no longer exists
        if (ResourceManager::Instance().displayMap.count(targetArrow.first) == 0)
        {
            Game::Instance().RemoveEntity(targetArrow.second);
            removedArrows.push_back(targetArrow.first);
            continue;
        }
        //if resource was deleted disable outgoing arrow since resource still exists in graph
        if (!ResourceManager::Instance().displayMap[targetArrow.first]->enabled)
        {
            targetArrow.second->enabled = false;
            continue;
        }
        targetArrow.second->enabled = true;
        DisplayNode* target = ResourceManager::Instance().displayMap[targetArrow.first];
        Vector2 dir = target->getCenterPos() - getCenterPos();
        dir.normalize();
        targetArrow.second->from = getCenterPos() + dir * size / 2;
        targetArrow.second->to = target->getCenterPos() - dir * size / 2;
    }

    for (size_t i = 0; i < removedArrows.size(); i++)
    {
        delete outgoingArrows[removedArrows[i]];
        outgoingArrows.erase(removedArrows[i]);
    }
}


void DisplayNode::render()
{
    if (!enabled) return;
    if (selected)
    {
        RenderWindow::Instance().render(Assets::Instance().img_selectedCircleNode, currentFrame, {int(pos.x * scale + viewportCenter.x * 4), int(pos.y * scale + viewportCenter.y * 4), int(currentFrame.w * scale), int(currentFrame.h * scale)}, 0);
    }
    else
    {
        RenderWindow::Instance().render(tex, currentFrame, { int(pos.x * scale + viewportCenter.x * 4), int(pos.y * scale + viewportCenter.y * 4), int(currentFrame.w * scale), int(currentFrame.h * scale) }, 0);
    }
    if (displayCraftButton)
    {
        RenderWindow::Instance().render(buttonState, currentFrame, { int(pos.x * scale + viewportCenter.x * 4), int(pos.y * scale + viewportCenter.y * 4), int(currentFrame.w * scale), int(currentFrame.h * scale) }, 0);
        renderTextAtVerticalOffset(craftTextImg, 9);
    }
    renderTextAtVerticalOffset(nameTextImg, -10);
    renderTextAtVerticalOffset(amountTextImg, -2);
}

void DisplayNode::updateTransformState()
{
    lastTransfromState = transformState;
    transformState = GameTransformer::Instance().getTransformState();
    this->scale = 4.0f * transformState.scale.x;
    transformState.translation /= scale;
    this->pos -= lastTransfromState.translation * lastTransfromState.scale / transformState.scale;
    this->pos += transformState.translation;
}

Vector2 DisplayNode::getScreenPos(Vector2 centerPos)
{
    return centerPos - size / 2;
}

Vector2 DisplayNode::getCenterPos()
{
    return pos + size / 2;
}

Vector2 DisplayNode::screenSpaceSize()
{
    return size * scale;
}
