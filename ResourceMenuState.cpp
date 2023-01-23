#include "ResourceMenuState.hpp"

ResourceMenuState::ResourceMenuState(std::string name)
	: GameState(name)
{}

void ResourceMenuState::start()
{
    //309, 0
    ScrollBar* scrollBar = new ScrollBar(90, 33, 4, Assets::Instance().img_ScrollBarSmall, 6);
    Entity* scrollArea = new Entity(90, 33, 4, Assets::Instance().img_ScrollArea, 5);
    ResourceManager::Instance().init(scrollBar, scrollArea);
    entities.push_back(new Entity(0, 0, 4, Assets::Instance().img_ListView, 3));
    entities.push_back(new Entity(0, 0, 4, Assets::Instance().img_GraphView, 1));
    entities.push_back(new Entity(0, 0, 4, Assets::Instance().img_GraphBorders, 3));
    entities.push_back(new Entity(0, 0, 4, Assets::Instance().img_ListBorders, 5));
    entities.push_back(new TextEntity(16, 40, 1, "Resource List", 32, { 0,0,0 }, Assets::Instance().font_Test, 30, 6));
    entities.push_back(scrollArea);
    entities.push_back(scrollBar);
    auto buttonPressedFunction = [this]() {nextState = "MainGameState"; };
    entities.push_back(new ButtonEntity(309, 0, 4, Assets::Instance().img_ExitButton, Assets::Instance().img_ExitButtonPressed, 6, buttonPressedFunction));
}

std::string ResourceMenuState::execute()
{
    nextState = name;
    if (InputManager::Instance().getIPressed())
        return "MainGameState";
    updateEntities();
    return nextState;
}