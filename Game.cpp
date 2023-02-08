#include "Game.hpp"


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
    static DisplayNode* previouslySelected = NULL;
    GameTransformer::Instance().pushTransformState();
    static Vector2 lastMousePos = Vector2(0, 0);
    static Vector2 dragOffset = Vector2(0, 0);
    int mouseWheelY = utils::roundFloat(InputManager::Instance().getMouseWheelY());
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
        DisplayNode* selected;
        if (previouslySelected == NULL)
        {
            selected = ResourceManager::Instance().getSelectedDisplayNode(mousePos);
        }
        else
            selected = previouslySelected;
        ResourceManager::Instance().updateSelectedText();
        Vector2 dragDir = InputManager::Instance().getMousePos() - lastMousePos;
        if (selected != NULL)
        {
            *selected->pos += dragDir / selected->scale;
        }
        else
            dragOffset += dragDir;

        previouslySelected = selected;
    }
    else
        previouslySelected = NULL;
    if (InputManager::Instance().getMouseReleased())
    {
        ResourceManager::Instance().checkCraftButtonPressed(mousePos);
    }
    lastMousePos = InputManager::Instance().getMousePos();
    GameTransformer::Instance().translate(dragOffset);
}

bool compareEntities(Entity* e1, Entity* e2)
{
    return e1->sortOrder < e2->sortOrder;
}

MainGameState* Game::GetMainGameState()
{
    return dynamic_cast<MainGameState*>(gameStateMap["MainGameState"]);
}

Uint32 Game::GetGameTime()
{
    if (gameStateMap.count("MainGameState") > 0)
        return dynamic_cast<MainGameState*>(gameStateMap["MainGameState"])->getGameTime();
    return 0;
}

void Game::init()
{
    currState = "StartMenuState";
    gameStateMap["ResourceMenuState"] = new ResourceMenuState("ResourceMenuState");
    gameStateMap["StartMenuState"] = new StartMenuState("StartMenuState");
    gameStateMap["MainGameState"] = new MainGameState("MainGameState");

    for (auto& pair : gameStateMap)
    {
        pair.second->start();
        sort(pair.second->entities.begin(), pair.second->entities.end(), compareEntities);
    }
    gameRunning = true;
    inputFuture = std::async(getInput);
    update();
}

void Game::QuitGame()
{
    gameRunning = false;
}

void Game::update()
{
    string line;
    SDL_Event event;
    std::string prevGameState;
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
        //execute game state
        prevGameState = currState;
        currState = gameStateMap[currState]->execute();
        if (currState != prevGameState)
        {
            gameStateMap[prevGameState]->onDeactivate();
            gameStateMap[currState]->onActivate();
        }
        //render
        for (size_t i = 0; i < gameStateMap[currState]->entities.size(); i++)
        {
            gameStateMap[currState]->entities[i]->render();
        }
        RenderWindow::Instance().display();
        GameTransformer::Instance().resetGameTransformations();
        InputManager::Instance().resetSingleFrameEvents();
        
        if (inputFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
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
    for (size_t i = 0; i < gameStateMap[currState]->entities.size(); i++)
    {
        if (gameStateMap[currState]->entities[i] == entity)
        {
            gameStateMap[currState]->entities.erase(gameStateMap[currState]->entities.begin() + i);
            break;
        }
    }
}

void Game::RemoveEntity(Entity* entity, std::string gameState)
{
    for (size_t i = 0; i < gameStateMap[gameState]->entities.size(); i++)
    {
        if (gameStateMap[gameState]->entities[i] == entity)
        {
            gameStateMap[gameState]->entities.erase(gameStateMap[gameState]->entities.begin() + i);
            break;
        }
    }
}

void Game::RemoveAndDeleteEntity(Entity* entity)
{
    for (size_t i = 0; i < gameStateMap[currState]->entities.size(); i++)
    {
        if (gameStateMap[currState]->entities[i] == entity)
        {
            gameStateMap[currState]->entities.erase(gameStateMap[currState]->entities.begin() + i);
            break;
        }
    }
    delete entity;
}

void Game::AddEntity(Entity* entity)
{
    gameStateMap[currState]->entities.push_back(entity);
    std::stable_sort(gameStateMap[currState]->entities.begin(), gameStateMap[currState]->entities.end(), compareEntities);
}

void Game::AddEntity(Entity* entity, std::string gameState)
{
    gameStateMap[gameState]->entities.push_back(entity);
     std::stable_sort(gameStateMap[gameState]->entities.begin(), gameStateMap[gameState]->entities.end(), compareEntities);
}

void Game::ResetGame()
{
    delete gameStateMap["MainGameState"];
    gameStateMap["MainGameState"] = new MainGameState("MainGameState");
    gameStateMap["MainGameState"]->start();
     std::stable_sort(gameStateMap["MainGameState"]->entities.begin(), gameStateMap["MainGameState"]->entities.end(), compareEntities);
    ResourceManager::Instance().resetResources();
}

Game& Game::Instance()
{
	static Game game;
	return game;
}

Game::Game() 
{
    gameRunning = false;
}

Game::~Game()
{
    for (auto& pair : gameStateMap)
    {
        delete pair.second;
    }
}
