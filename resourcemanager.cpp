#include "ResourceManager.hpp"

ResourceManager& ResourceManager::Instance()
{
    static ResourceManager resourceManager;
    return resourceManager;
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


void ResourceManager::deleteResource(string resource, std::vector<TextEntity*> &resourceList)
{
    resourceMap.erase(resource);
    displayGraph(resourceList);
}

void ResourceManager::addNode(string node, std::vector<TextEntity*> &resourceList)
{
    if (resourceMap.count(node) == 0)
    {
        resourceMap[node] = new Resource(node);
    }
    else
    {
        cout << "Resource " << node << "already exists in graph\n";
    }
    displayGraph(resourceList);
}

void ResourceManager::addLink(string from, string to, std::vector<TextEntity*> &resourceList)
{
    if (resourceMap.count(from) == 0)
    {
        cout << "Resource " << from << " does not exist in graph\n";
        return;
    }
    resourceMap[from]->requiredResources.push_back(to);
    displayGraph(resourceList);
}

void ResourceManager::displayGraph(std::vector<TextEntity*> &resourceList)
{
    cout << "Current Resource graph:" << endl;
    size_t mapSize = resourceMap.size();
    //TODO fix potential memory leak when resizing
    resourceList.resize(mapSize);
    int i = 0;
    for (auto const& pair : resourceMap)
    {
        std::string text = pair.first;
        if (isCraftable(*pair.second))
            text += " usable";
        else
            text += " not usable";   
        if (resourceList[i] != NULL) {
            resourceList[i]->updateText(text);
        }
        else
        {
            float x = 10;
            float y = 150 + float(i) * 40;
            resourceList[i] = new TextEntity(x, y, 1, text, 25, { 0,0,0 }, Assets::Instance().font_Test);
        }
        i++;
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

map<string, Resource*> resourceMap;
ResourceManager::ResourceManager() {}
