#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
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

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

/*
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
*/

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
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
    return EXIT_SUCCESS;
}