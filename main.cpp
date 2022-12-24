#include <SDL_image.h>
#include <SDL.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <SDL_ttf.h>
#include "Resource.hpp"
#include "RenderWindow.hpp"
#include "Vector2.hpp"
#include "ResourceManager.hpp"
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
    PrintMemoryUsage();
}

void buildGraph(ifstream& file)
{
    string line;
    while (getline(file, line))
    {
        ResourceManager::Instance().addResource(line);
    }
}

const int WIDTH = 800, HEIGHT = 600;
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
    SDL_Texture* testTexture = window.loadTexture("Assets/images/TestSprite.png");
    TTF_Font* font = TTF_OpenFont("Assets/fonts/pixel-bit-advanced.ttf", 30);
    SDL_Surface* textSurf = TTF_RenderText_Solid(font, "Hello World", { 0,0,0 });
    SDL_Texture* textTexture = window.createFontTexture(textSurf);
    SDL_Rect textRect = { 200, 200, textSurf->w, textSurf->h };
    SDL_FreeSurface(textSurf);
    TTF_CloseFont(font);


    Entity testEntity(0, 0, testTexture);
    Entity textEntity(0, 0, textTexture);
    bool gameRunning = true;
    SDL_Event event;
    utils::hireTimeInSeconds();
    while (gameRunning)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                gameRunning = false;
        }
        window.clear();
        window.render(testEntity);
        window.renderUnscaled(textEntity);
        window.display();
        string line;
        std::getline(std::cin, line);
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
    ResourceManager::Instance().outputGraph("OutResources.txt");
    window.cleanUp();
    IMG_Quit();
    SDL_Quit();
    PrintMemoryUsage();
    return EXIT_SUCCESS;
}