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

void buildGraph(ifstream& file)
{
    bool startWithResources = true;
    string line;
    while (getline(file, line))
    {
        if (line == "start without")
            startWithResources = false;
        else
            ResourceManager::Instance().addResource(line, startWithResources);
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
    std::string resourceFile = "resources.txt";
    if (argc == 2)
        resourceFile = argv[1];
    ifstream file(resourceFile);
    if (!file.good())
    {
        cout << "ERROR: problem reading file " << resourceFile
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