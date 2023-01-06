#include "Game.hpp"
#include "ResourceListText.hpp"
#include "ScrollBar.hpp"
#include "ResourceManager.hpp"
#include "InputManager.hpp"
#include "ArrowEntity.hpp"
#include "DisplayNode.hpp"

static std::string getInput()
{
    std::string answer;
    getline(std::cin, answer);
    return answer;
}

void processCommand(std::string line, bool& gameRunning)
{
    vector<string> command = utils::split(line, ' ');
    if (command.size() > 0)
    {
        if (command[0] == "del")
        {
            if (command.size() == 2)
            {
                ResourceManager::Instance().deleteResource(command[1]);
            }
            else
                cout << "Invocation: del [resource name]\n";
        }
        else if (command[0] == "add")
        {
            if (command.size() == 2)
            {
                ResourceManager::Instance().addNode(command[1]);
            }
            else
                cout << "Invocation: add [resource name]\n";
        }
        else if (command[0] == "link")
        {
            if (command.size() == 3)
            {
                ResourceManager::Instance().addLink(command[1], command[2]);
            }
            else
                cout << "Invocation: link [resource to craft] [required resource]\n";
        }
        else if (command[0] == "erase")
        {
            if (command.size() == 2)
            {
                ResourceManager::Instance().erase(command[1]);
            }
            else
                cout << "Invocation: erase [resource to erase]\n";
        }
        else if (command[0] == "unlink")
        {
            if (command.size() == 3)
            {
                ResourceManager::Instance().unLink(command[1], command[2]);
            }
            else
                cout << "Invocation: add [resource to craft] [required resource]\n";
        }
        else if (command[0] == "q")
        {
            gameRunning = false;
        }
    }
}

void handleDragInput()
{
    GameTransformer::Instance().pushTransformState();
    static Vector2 lastMousePos = Vector2(0, 0);
    static Vector2 dragOffset = Vector2(0, 0);
    int mouseWheelY = InputManager::Instance().getMouseWheelY();
    if (mouseWheelY == 0)
        GameTransformer::Instance().setScale(Vector2(1, 1));
    if (mouseWheelY == -1)
        GameTransformer::Instance().setScale(Vector2(.5, .5));
    if (mouseWheelY == -2)
        GameTransformer::Instance().setScale(Vector2(.25, .25));
    Vector2 mousePos = InputManager::Instance().getMousePos() / 4;
    //mouse is down and inside viewport
    if (InputManager::Instance().getMouseDown() && mousePos.x > 97)
    {
        DisplayNode* selected = ResourceManager::Instance().getSelectedDisplayNode(mousePos);
        Vector2 dragDir = InputManager::Instance().getMousePos() - lastMousePos;
        if (selected != NULL)
            *selected->pos += dragDir / selected->scale;
        else
            dragOffset += dragDir;
    }
    lastMousePos = InputManager::Instance().getMousePos();
    GameTransformer::Instance().translate(dragOffset);
}

bool compareEntities(Entity* e1, Entity* e2)
{
    return e1->sortOrder < e2->sortOrder;
}

void Game::init()
{
    ScrollBar* scrollBar = new ScrollBar(90, 33, 4, Assets::Instance().img_ScrollBarSmall, 6);
    Entity* scrollArea = new Entity(90, 33, 4, Assets::Instance().img_ScrollArea, 5);
    ResourceManager::Instance().init(scrollBar, scrollArea);
    entities.push_back(new Entity(0, 0, 4, Assets::Instance().img_ListView, 3));
    entities.push_back(new Entity(0, 0, 4, Assets::Instance().img_GraphView, 1));
    entities.push_back(new Entity(0, 0, 4, Assets::Instance().img_GraphBorders, 3));
    entities.push_back(new Entity(0, 0, 4, Assets::Instance().img_ListBorders, 5));
    entities.push_back(new TextEntity(16, 40, 1, "Resource List", 32, { 0,0,0 }, Assets::Instance().font_Test, 5));
    entities.push_back(scrollArea);
    entities.push_back(scrollBar);
    sort(entities.begin(), entities.end(), compareEntities);
    gameRunning = true;
    inputFuture = std::async(getInput);
    update();
}

void Game::update()
{
    string line;
    SDL_Event event;
    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            InputManager::Instance().handleInput(event);
            if (event.type == SDL_QUIT)
                gameRunning = false;
        }
        handleDragInput();
        RenderWindow::Instance().clear();
        for (int i = 0; i < entities.size(); i++)
        {
            entities[i]->update();
            entities[i]->render();
        }
        RenderWindow::Instance().display();
        GameTransformer::Instance().resetGameTransformations();
        if (inputFuture._Is_ready())
        {
            line = inputFuture.get();
            processCommand(line, gameRunning);
            if (gameRunning)
                inputFuture = std::async(getInput);
        }
    }
}

void Game::RemoveEntity(Entity* entity)
{
    remove(entities.begin(), entities.end(), entity);
    entities.resize(entities.size() - 1);
}


void Game::AddEntity(Entity* entity)
{
    entities.push_back(entity);
    sort(entities.begin(), entities.end(), compareEntities);
}

Game& Game::Instance()
{
	static Game game;
	return game;
}

Game::Game() {}

Game::~Game()
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i] != NULL)
            delete entities[i];
    }
}
