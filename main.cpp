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
#include "ResourceListText.hpp"
#include "Game.hpp"
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

int main (int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
        cout << "SDL_Init HAS FAILED. ADL_ERROR: " << SDL_GetError() << endl;
    if (!IMG_Init(IMG_INIT_PNG))
        cout << "IMG_Init has failed" << SDL_GetError() << endl;
    if (TTF_Init() > 0)
        cout << "TTF_Init has failed" << SDL_GetError() << endl;
    Assets::Instance().loadAssets();
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
    Game::Instance().init();
    Assets::Instance().closeFonts();
    ResourceManager::Instance().outputGraph("OutResources.txt");
    RenderWindow::Instance().cleanUp();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}