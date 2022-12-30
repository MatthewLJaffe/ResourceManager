#include "Game.hpp"
#include "ResourceListText.hpp"
#include "ScrollBar.hpp"
#include "ResourceManager.hpp"
#include "InputManager.hpp"

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
                cout << "Invocation: add [resource to craft] [required resource]\n";
        }
        else if (command[0] == "q")
        {
            gameRunning = false;
        }
    }
}

bool compareEntities(Entity* e1, Entity* e2)
{
    return e1->sortOrder < e2->sortOrder;
}

void Game::init()
{
    entities.resize(0);
    ScrollBar* scrollBar = new ScrollBar(90, 33, 4, Assets::Instance().img_ScrollBarSmall, 3);
    Entity* scrollArea = new Entity(90, 33, 4, Assets::Instance().img_ScrollArea, 2);
    ResourceManager::Instance().init(scrollBar, scrollArea);
    //Text rendering
    entities.push_back(new Entity(0, 0, 4, Assets::Instance().img_Background, 0));
    entities.push_back(new Entity(0, 0, 4, Assets::Instance().img_OverList, 2));
    //entities.push_back(new TextEntity(16, 40, 1, "Resource List", 32, { 0,0,0 }, Assets::Instance().font_Test, 2));
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
        if (SDL_PollEvent(&event))
        {
            InputManager::Instance().handleInput(event);
            if (event.type == SDL_QUIT)
                gameRunning = false;
        }
        RenderWindow::Instance().clear();
        for (int i = 0; i < entities.size(); i++)
        {
            entities[i]->update();
            entities[i]->render();
        }
        RenderWindow::Instance().display();
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
