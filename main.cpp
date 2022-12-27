#include <SDL_image.h>
#include <SDL.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <future>
#include <thread>
#include <SDL_ttf.h>
#include "Resource.hpp"
#include "RenderWindow.hpp"
#include "Vector2.hpp"
#include "ResourceManager.hpp"
#include "Assets.hpp"
#include "TextEntity.hpp"
using namespace std;


struct AllocationMetrics
{
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;

    uint32_t CurrentUsage()
    {
        return TotalAllocated - TotalFreed;
    }
};
static AllocationMetrics s_AllocationMetrics;

static void PrintMemoryUsage()
{
    cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}

void* operator new(size_t size)
{
    s_AllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void* memory, size_t size)
{
    s_AllocationMetrics.TotalFreed += size;
    free(memory);
    //PrintMemoryUsage();
}

void buildGraph(ifstream& file)
{
    string line;
    while (getline(file, line))
    {
        ResourceManager::Instance().addResource(line);
    }
}

static std::string getInput()
{
    std::string answer;
    getline(std::cin, answer);
    return answer;
}

const int WIDTH = 1280, HEIGHT = 720;
int main (int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
        cout << "SDL_Init HAS FAILED. ADL_ERROR: " << SDL_GetError() << endl;
    if (!IMG_Init(IMG_INIT_PNG))
        cout << "IMG_Init has failed" << SDL_GetError() << endl;
    if (TTF_Init() > 0)
        cout << "TTF_Init has failed" << SDL_GetError() << endl;

    if (argc != 2)
    {
        cout << "Invocation: " << "./ResourceManager.exe {resourceFile}" << endl;
        return 1;
    }
    ifstream file(argv[1]);
    if (!file.good())
    {
        cout << "ERROR: problem reading file " << argv[1]
            << " make sure file is in same directory as executable\n";
        return 1;
    }
    buildGraph(file);
    cout<< argv[1] << endl;
    RenderWindow window("Resource Manager", WIDTH, HEIGHT);
    //Text rendering
    Assets::Instance().loadAssets(&window);
    std::vector<Entity*> entities;
    entities.push_back(new Entity (0, 0, 4, Assets::Instance().img_Background));
    entities.push_back(new TextEntity(16, 40, 1, "Resource List", 32, { 0,0,0 }, Assets::Instance().font_Test, &window));
    bool gameRunning = true;
    SDL_Event event;
    utils::hireTimeInSeconds();
    std::future<std::string> future = std::async(getInput);
    while (gameRunning)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                gameRunning = false;
        }
        window.clear();
        for (int i = 0; i < entities.size(); i++)
        {
            entities[i]->update();
            window.render(*entities[i]);
        }
        window.display();
        string line;
        if (future._Is_ready())
        {
            line = future.get();
            future = std::async(getInput);
        }
        else
        {
            continue;
        }
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
    Assets::Instance().closeFonts();
    ResourceManager::Instance().outputGraph("OutResources.txt");
    window.cleanUp();
    IMG_Quit();
    SDL_Quit();
    PrintMemoryUsage();
    return EXIT_SUCCESS;
}