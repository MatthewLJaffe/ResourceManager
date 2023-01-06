#include "ResourceManager.hpp"
#include "Utils.hpp"

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
    if (resources.size() == 0) return;
    Resource* resource;
    if (resourceMap.count(resources[0])) {
        resource = resourceMap[resources[0]];
    }
    else {
        resource = new Resource(resources[0]);
        resourceMap[resource->name] = resource;
        addNewDisplayNode(resources[0]);
    }
    resource->requiredResources = vector<string>();
    for (size_t i = 1; i < resources.size(); i++)
    {
        if (resourceMap.count(resources[i]))
        {
            resource->requiredResources.push_back(resources[i]);
            addDisplayNodeConnection(resources[0], resources[i]);
        }
        else
        {
            Resource* reqResource = new Resource(resources[i]);
            resource->requiredResources.push_back(resources[i]);
            resourceMap[reqResource->name] = reqResource;
            addNewDisplayNodeFrom(resource->name, reqResource->name);
        }
    }
}

bool ResourceManager::isCraftable(Resource& resource, std::map<string, bool> visitedMap)
{
    if (visitedMap.count(resource.name) > 0)
    {
        return true;
    }
    visitedMap[resource.name] = true;
    for (size_t i = 0; i < resource.requiredResources.size(); i++)
    {
        //if erase was called on resource remove it from required resources since it no longer exists
        if (resourceMap.count(resource.requiredResources[i]) == 0)
        {
            resource.requiredResources.erase(resource.requiredResources.begin() + i);
            i--;
            continue;
        }
        if (!resourceMap[resource.requiredResources[i]]->active ||
            !isCraftable(*resourceMap[resource.requiredResources[i]], visitedMap))
            return false;
    }
    return true;
}

void ResourceManager::deleteResource(string resource)
{
    if (resourceMap.count(resource) == 0)
    {
        std::cout << "Resource: " << resource << " does not exist in the graph" << std::endl;
        return;
    }
    resourceMap[resource]->active = false;
    DisplayNode* removedNode = displayMap[resource];
    for (int i = 0; i < removedNode->outgoingArrows.size(); i++)
        removedNode->outgoingArrows[i]->arrow->enabled = false;
    removedNode->enabled = false;
    displayGraph();
}

void ResourceManager::erase(std::string resourceName)
{
    if (resourceMap.count(resourceName) == 0)
    {
        std::cout << "Resource: " << resourceName << " does not exist in the graph" << std::endl;
        return;
    }
    Resource* resourceObj = resourceMap[resourceName];
    resourceMap.erase(resourceName);
    delete resourceObj;
    DisplayNode* removedNode = displayMap[resourceName];
    for (int i = 0; i < removedNode->outgoingArrows.size(); i++)
    {
        Game::Instance().RemoveEntity(removedNode->outgoingArrows[i]->arrow);
        delete removedNode->outgoingArrows[i]->arrow;
    }
    Game::Instance().RemoveEntity(removedNode);
    delete removedNode;
    displayMap.erase(resourceName);
    displayGraph();
}

void ResourceManager::unLink(std::string from, std::string to)
{
    if (resourceMap.count(from) == 0)
    {
        cout << "Resource " << from << " does not exist in graph\n";
        return;
    }
    if (resourceMap.count(to) == 0)
    {
        cout << "Resource " << to << " does not exist in graph\n";
        return;
    }
    for (int i = 0; i < resourceMap[from]->requiredResources.size(); i++)
    {
        if (resourceMap[from]->requiredResources[i] == to)
        {
            resourceMap[from]->requiredResources.erase(resourceMap[from]->requiredResources.begin() + i);
            break;
        }
    }
    for (int i = 0; i < displayMap[from]->outgoingArrows.size(); i++)
    {
        if (displayMap[from]->outgoingArrows[i]->target == to)
        {
            Game::Instance().RemoveEntity(displayMap[from]->outgoingArrows[i]->arrow);
            displayMap[from]->outgoingArrows.erase(displayMap[from]->outgoingArrows.begin() + i);
            break;
        }
    }
}

void ResourceManager::addNode(string node)
{
    if (resourceMap.count(node) == 0)
    {
        resourceMap[node] = new Resource(node);
        addNewDisplayNode(node);
    }
    else if (!resourceMap[node]->active)
    {
        resourceMap[node]->active = true;
        DisplayNode* removedNode = displayMap[node];
        for (int i = 0; i < removedNode->outgoingArrows.size(); i++)
            removedNode->outgoingArrows[i]->arrow->enabled = true;
        removedNode->enabled = true;
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
    if (!resourceMap[from]->active)
    {
        cout << "Resource " << from << " must be active in graph to create link\n";
        return;
    }
    resourceMap[from]->requiredResources.push_back(to);
    if (displayMap.count(to) == 0)
    {
        resourceMap[to] = new Resource(to);
        addNewDisplayNodeFrom(from, to);
    }
    else
        addDisplayNodeConnection(from, to);
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
    std::map<string, bool> visitedMap;
    for (auto const& pair : resourceMap)
    {
        visitedMap.clear();
        std::string text = pair.first;
        if (isCraftable(*pair.second, visitedMap))
            text += " usable";
        else
            text += " not usable";   
        float x = 10;
        float y = 150 + float(i) * textHeight;
        listText[i] = new ResourceListText(x, y, 1, text, 25, {0,0,0}, Assets::Instance().font_Test, 4);
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

void ResourceManager::addNewDisplayNode(std::string name)
{
    Vector2 newPos(-24, -24);
    //make newpos opposite to average pos
    if (displayMap.size() > 0)
    {
        newPos.x = 0;
        newPos.y = 0;
        for (auto const& pair : displayMap)
        {
            newPos += *pair.second->pos;
        }
        newPos /= -float(displayMap.size());
        Vector2 minOffset(-48, -24);
        Vector2 maxOffset(48, 24);
        int tries = 0;
        bool placed = false;
        while (!placed)
        {
            if (tries > 10)
            {
                tries = 0;
                minOffset.x -= 24;
                minOffset.y -= 24;
                maxOffset.x += 24;
                maxOffset.y += 24;
            }
            newPos.x += utils::randomFloat(minOffset.x, maxOffset.x);
            newPos.y += utils::randomFloat(minOffset.y, maxOffset.y);
            if (noOverlap(newPos))
                placed = true;
            tries++;
        }
    }
    DisplayNode* displayNode = new DisplayNode(newPos.x, newPos.y, 4, Assets::Instance().img_circleNode, 2, name);
    displayMap[name] = displayNode;
    Game::Instance().AddEntity(displayNode);
}

void ResourceManager::addNewDisplayNodeFrom(std::string from, std::string name)
{
    Vector2 minOffset(-24, -24);
    Vector2 maxOffset(24, 24);
    DisplayNode* fromNode = displayMap[from];
    Vector2 newPos(0, 0);
    if (fromNode->points.size() > 0)
    {
        for (int i = 0; i < fromNode->points.size(); i++)
        {
            newPos += fromNode->points[i];
        }
        newPos /= -float(fromNode->points.size());
        newPos += *fromNode->pos;
    }
    else
    {
        newPos.x = fromNode->pos->x + 64;
        newPos.y = fromNode->pos->y;
    }
    
    int tries = 0;
    bool placed = false;
    while (!placed)
    {
        if (tries > 10)
        {
            tries = 0;
            minOffset.x -= 24;
            minOffset.y -= 24;
            maxOffset.x += 24;
            maxOffset.y += 24;
        }
        newPos.x += utils::randomFloat(minOffset.x, maxOffset.x);
        newPos.y += utils::randomFloat(minOffset.y, maxOffset.y);
        if (noOverlap(newPos))
            placed = true;
        tries++;
    }
    DisplayNode* displayNode = new DisplayNode(newPos.x, newPos.y, 4, Assets::Instance().img_circleNode, 2, name);
    displayMap[name] = displayNode;
    Game::Instance().AddEntity(displayNode);
    addDisplayNodeConnection(from, name);
}

void ResourceManager::addDisplayNodeConnection(std::string from, std::string to)
{
    if (displayMap.count(from) == 0 || displayMap.count(to) == 0) return;
    DisplayNode* fromNode = displayMap[from];
    DisplayNode* toNode = displayMap[to];
    Vector2 fromPos = fromNode->getCenterPos();
    Vector2 toPos = toNode->getCenterPos();
    Vector2 dir = toPos - fromPos;
    dir.normalize();
    
    Vector2 fromOffset = Vector2(dir.x * 24, dir.y * 24);
    Vector2 toOffset= Vector2(-dir.x * 24, -dir.y * 24);
    Vector2* arrowStart = new Vector2(fromPos.x + fromOffset.x, fromPos.y + fromOffset.y);
    Vector2* arrowEnd = new Vector2(toPos.x + toOffset.x, toPos.y + toOffset.y);
    ArrowEntity* arrow = new ArrowEntity(arrowStart, arrowEnd, 4, NULL, 2);
    fromNode->outgoingArrows.push_back(new OutgoingArrow(to, arrow));
    fromNode->points.push_back(fromOffset);
    toNode->points.push_back(toOffset);
    Game::Instance().AddEntity(arrow);
}

bool ResourceManager::noOverlap(Vector2 pos)
{
    for (auto const& pair : displayMap)
    {
        if (pos.distance(*pair.second->pos) <= 64)
            return false;
    }
    return true;
}

DisplayNode* ResourceManager::getSelectedDisplayNode(Vector2 mousePos)
{
    for (auto const& pair : displayMap)
    {
        Vector2 nodeScreenPos = pair.second->getCenterPos() * pair.second->scale / 4 + pair.second->viewportCenter;
        if (nodeScreenPos.distance(mousePos) < pair.second->size.x/2 * pair.second->scale/4)
            return pair.second;
    }
    return NULL;
}

map<string, Resource*> resourceMap;
ResourceManager::ResourceManager() {}
