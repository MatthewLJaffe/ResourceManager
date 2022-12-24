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

void ResourceManager::displayGraph()
{
    cout << "Current Resource graph:" << endl;
    for (auto const& pair : resourceMap)
    {
        cout << pair.first;
        if (isCraftable(*pair.second))
            cout << " usable" << endl;
        else
            cout << " not usable" << endl;
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
