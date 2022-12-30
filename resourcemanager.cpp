#include "ResourceManager.hpp"

ScrollBarVariation::ScrollBarVariation(SDL_Texture* tex, int maxScrollHeight, int minNumberItems)
{
    this->texture = tex;
    this->maxScrollHeight = maxScrollHeight;
    this->minNumberItems = minNumberItems;
}


ResourceManager& ResourceManager::Instance()
{
    static ResourceManager resourceManager;
    return resourceManager;
}

void ResourceManager::init(ScrollBar* scrollBar, Entity* scrollArea)
{
    scrollBar->enabled = false;
    scrollArea->enabled = false;
    this->scrollBar = scrollBar;
    this->scrollArea = scrollArea;
    scrollBarVariations[0].texture = Assets::Instance().img_ScrollBarSmall;
    scrollBarVariations[1].texture = Assets::Instance().img_ScrollBarMed;
    scrollBarVariations[2].texture = Assets::Instance().img_ScrollBarLarge;
    displayGraph();
}

void ResourceManager::addResource(string line)
{
    vector<string> resources = utils::split(line, ' ');
    Resource* resource;
    if (resourceMap.count(resources[0])) {
        resource = resourceMap[resources[0]];
    }
    else {
        resource = new Resource(resources[0]);
        resourceMap[resource->name] = resource;
    }
    resource->requiredResources = vector<string>();
    for (size_t i = 1; i < resources.size(); i++)
    {
        if (resourceMap.count(resources[i]))
        {
            resource->requiredResources.push_back(resources[i]);
        }
        else
        {
            Resource* reqResource = new Resource(resources[i]);
            resource->requiredResources.push_back(resources[i]);
            resourceMap[reqResource->name] = reqResource;
        }
    }
}

bool ResourceManager::isCraftable(Resource& resource)
{
    for (size_t i = 0; i < resource.requiredResources.size(); i++)
    {
        if (resourceMap.count(resource.requiredResources[i]) == 0 ||
            !isCraftable(*resourceMap[resource.requiredResources[i]]))
            return false;
    }
    return true;
}

void ResourceManager::deleteResource(string resource)
{
    resourceMap.erase(resource);
    displayGraph();
}

void ResourceManager::addNode(string node)
{
    if (resourceMap.count(node) == 0)
    {
        resourceMap[node] = new Resource(node);
    }
    else
    {
        cout << "Resource " << node << "already exists in graph\n";
    }
    displayGraph();
}

void ResourceManager::addLink(string from, string to)
{
    if (resourceMap.count(from) == 0)
    {
        cout << "Resource " << from << " does not exist in graph\n";
        return;
    }
    resourceMap[from]->requiredResources.push_back(to);
    displayGraph();
}

//TODO only rebuild display for delete
void ResourceManager::displayGraph()
{
    for (int i = 0; i < listText.size(); i++)
    {
        Game::Instance().RemoveEntity(listText[i]);
        delete listText[i];
    }
    size_t mapSize = resourceMap.size();
    listText.resize(mapSize);
    int i = 0;
    for (auto const& pair : resourceMap)
    {
        std::string text = pair.first;
        if (isCraftable(*pair.second))
            text += " usable";
        else
            text += " not usable";   
        float x = 10;
        float y = 150 + float(i) * textHeight;
        listText[i] = new ResourceListText(x, y, 1, text, 25, {0,0,0}, Assets::Instance().font_Test, 1);
        Game::Instance().AddEntity(listText[i]);
        i++;
    }
    if (mapSize > maxNonScrollListItems)
    {
        scrollArea->enabled = true;
        scrollBar->enabled = true;
        for (int i = 0; i < 3; i++)
        {
            if (scrollBarVariations[i].minNumberItems <= mapSize)
            {
                scrollBar->ResizeScrollBar(scrollBarVariations[i].texture, scrollBarVariations[i].maxScrollHeight);
                break;
            }
        }
    }
}

void ResourceManager::outputGraph(string fileName)
{
    ofstream file(fileName);
    if (!file.good())
    {
        std::cout << "Error writing to file " << fileName << std::endl;
        return;
    }
    for (auto const& pair : resourceMap)
    {
        file << pair.first;
        for (size_t i = 0; i < pair.second->requiredResources.size(); i++)
        {
            file << " " + pair.second->requiredResources[i];
        }
        file << std::endl;
    }
    file.close();
}

float ResourceManager::getMaxTextOffset()
{
    return (resourceMap.size() - maxNonScrollListItems) * textHeight;
}

ResourceManager::~ResourceManager()
{
    for (auto const& pair : resourceMap)
    {
        delete pair.second;
    }
}

map<string, Resource*> resourceMap;
ResourceManager::ResourceManager() {}
