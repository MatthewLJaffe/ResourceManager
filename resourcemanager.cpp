#include "ResourceManager.hpp"

map<string, Resource*> resourceMap;

TraversalInfo::TraversalInfo()
{
    //-1 denotes not sure how many are craftable yet
    amountObtainable = -1;
    visited = false;
}


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

void ResourceManager::addResource(string line, bool startWithResource)
{
    vector<string> resources = utils::split(line, ' ');
    if (resources.size() == 0) return;
    Resource* resource;
    if (resourceMap.count(resources[0])) {
        resource = resourceMap[resources[0]];
    }
    else {
        resource = new Resource(resources[0]);
        if (startWithResource)
            resource->amount = 1;
        resourceMap[resource->name] = resource;
    }
    resource->requiredResources = vector<ResourceAmount>();
    for (size_t i = 1; i < resources.size(); i++)
    {
        size_t leftBracketPos = resources[i].find('[');
        size_t rightBracketPos = resources[i].find(']');
        int amount = 1;
        std::string resourceStr = resources[i];
        if (leftBracketPos != std::string::npos && rightBracketPos != std::string::npos && rightBracketPos > leftBracketPos)
        {
            string amountStr = resources[i].substr(leftBracketPos + 1, rightBracketPos - 1 - leftBracketPos);
            resourceStr = resources[i].substr(0, leftBracketPos);
            try
            {
                amount = std::stoi(amountStr);
            }
            catch (std::invalid_argument& e) 
            {
                std::cout << e.what() << " invalid amount " << amountStr << std::endl;
                return;
            }
        }
        if (resourceMap.count(resourceStr))
        {
            resource->requiredResources.push_back(ResourceAmount(resourceStr, amount));
        }
        else
        {
            Resource* reqResource = new Resource(resourceStr);
            if (startWithResource)
                reqResource->amount = 1;
            resource->requiredResources.push_back(ResourceAmount(resourceStr, amount));
            resourceMap[reqResource->name] = reqResource;
        }
    }
}

void ResourceManager::deleteResource(string resource)
{
    size_t leftBracketPos = resource.find('[');
    size_t rightBracketPos = resource.find(']');
    int amount = 1;
    std::string resourceStr = resource;
    if (leftBracketPos != std::string::npos && rightBracketPos != std::string::npos && rightBracketPos > leftBracketPos)
    {
        string amountStr = resource.substr(leftBracketPos + 1, rightBracketPos - 1 - leftBracketPos);
        resourceStr = resource.substr(0, leftBracketPos);
        try
        {
            amount = std::stoi(amountStr);
            if (amount <= 0)
            {
                std::cout << "Amount must be positive integer" << std::endl;
                return;
            }
        }
        catch (std::invalid_argument& e)
        {
            std::cout << e.what() << " invalid amount " << amountStr << std::endl;
            return;
        }
    }
    if (resourceMap.count(resourceStr) == 0)
    {
        std::cout << "Resource: " << resourceStr << " does not exist in the graph" << std::endl;
        return;
    }
    if (resourceMap[resourceStr]->amount <= amount)
        setResourceAmount(resourceStr, 0);
    else if (resourceMap[resourceStr]->amount > 0)
        setResourceAmount(resourceStr, resourceMap[resourceStr]->amount - amount);
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
    for (auto& pair : removedNode->outgoingArrows)
    {
        Game::Instance().RemoveEntity(pair.second, "ResourceMenuState");
        delete pair.second;
    }
    Game::Instance().RemoveEntity(removedNode, "ResourceMenuState");
    delete removedNode;
    displayMap.erase(resourceName);
    //required resource refrences to erased resource are cleaned up in display graph
    displayGraph();
}

void ResourceManager::resetResources()
{
    for (auto& pair : resourceMap)
    {
        pair.second->amount = 0;
    }
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
    for (size_t i = 0; i < resourceMap[from]->requiredResources.size(); i++)
    {
        if (resourceMap[from]->requiredResources[i].resource == to)
        {
            resourceMap[from]->requiredResources.erase(resourceMap[from]->requiredResources.begin() + i);
            break;
        }
    }
    ArrowEntity* removedArrow = displayMap[from]->outgoingArrows[to];
    Game::Instance().RemoveEntity(removedArrow, "ResourceMenuState");
    displayMap[from]->outgoingArrows.erase(to);
    delete removedArrow;
    displayGraph();
}

void ResourceManager::addLink(string from, string to)
{
    int resourceAmount = 1;
    size_t leftBracketPos = to.find('[');
    size_t rightBracketPos = to.find(']');
    string resourceStr = to;
    if (leftBracketPos != std::string::npos && rightBracketPos != std::string::npos && rightBracketPos > leftBracketPos)
    {
        string amountStr = to.substr(leftBracketPos + 1, rightBracketPos - 1 - leftBracketPos);
        resourceStr = to.substr(0, leftBracketPos);
        try
        {
            resourceAmount = std::stoi(amountStr);
            if (resourceAmount <= 0)
            {
                std::cout << "amount must be positive integer " << std::endl;
                return;
            }
        }
        catch (std::invalid_argument& e)
        {
            std::cout << e.what() << " invalid amount " << amountStr << std::endl;
            return;
        }
    }
    if (resourceMap.count(from) == 0)
    {
        cout << "Resource " << from << " does not exist in graph\n";
        return;
    }
    for (size_t i = 0; i < resourceMap[from]->requiredResources.size(); i++)
    {
        if (resourceMap[from]->requiredResources[i].resource == resourceStr)
        {
            std::cout << "Resouce " << resourceStr << " already required to make " << from << std::endl;
            return;
        }
    }
    resourceMap[from]->requiredResources.push_back(ResourceAmount(resourceStr, resourceAmount));
    if (resourceMap.count(resourceStr) == 0)
    {
        resourceMap[resourceStr] = new Resource(resourceStr);
    }
    displayGraph();
}

void ResourceManager::addNode(string node)
{
    size_t leftBracketPos = node.find('[');
    size_t rightBracketPos = node.find(']');
    string resourceStr = node;
    int resourceAmount = 1;
    if (leftBracketPos != std::string::npos && rightBracketPos != std::string::npos && rightBracketPos > leftBracketPos)
    {
        string amountStr = node.substr(leftBracketPos + 1, rightBracketPos - 1 - leftBracketPos);
        resourceStr = node.substr(0, leftBracketPos);
        try
        {
            resourceAmount = std::stoi(amountStr);
            if (resourceAmount <= 0)
            {
                std::cout << "amount must be positive integer " << std::endl;
                return;
            }
        }
        catch (std::invalid_argument& e)
        {
            std::cout << e.what() << " invalid amount " << amountStr << std::endl;
            return;
        }
    }
    if (resourceMap.count(resourceStr) == 0)
    {
        resourceMap[resourceStr] = new Resource(resourceStr);
        resourceMap[resourceStr]->amount = resourceAmount;
    }
    else
    {
        setResourceAmount(resourceStr, resourceMap[resourceStr]->amount + resourceAmount);
    }
    displayGraph();
}

void ResourceManager::setResourceAmount(std::string resource, int amount)
{
    resourceMap[resource]->amount = amount;
    displayMap[resource]->setDisplayAmount(amount);
}

void ResourceManager::checkCraftButtonPressed(Vector2 mousePos)
{
    for (auto& pair : displayMap)
    {
        if (pair.second->posInCraftButton(mousePos))
        {
            craftResource(pair.first);
        }
    }
}

void ResourceManager::craftResource(std::string resourceName)
{
    if (resourceMap.count(resourceName) == 0) return;
    Resource* resource = resourceMap[resourceName];
    for (size_t i = 0; i < resource->requiredResources.size(); i++)
    {
        if (resourceMap[resource->requiredResources[i].resource]->amount < resource->requiredResources[i].amount)
            return;
    }
    for (size_t i = 0; i < resource->requiredResources.size(); i++)
    {
        setResourceAmount(resource->requiredResources[i].resource, resourceMap[resource->requiredResources[i].resource]->amount - resource->requiredResources[i].amount);
    }
    setResourceAmount(resourceName, resource->amount + 1);
    displayGraph();
}

void ResourceManager::displayGraph()
{
    //rebuild display from backend graph
    for (auto& pair : resourceMap)
    {
        if (displayMap.count(pair.first) == 0)
        {
            addNewDisplayNode(pair.first, pair.second->amount);
        }
        for (size_t i = 0; i < resourceMap[pair.first]->requiredResources.size(); i++)
        {
            ResourceAmount requiredResource = resourceMap[pair.first]->requiredResources[i];
            //resource was erased and no longer exists in graph
            if (resourceMap.count(requiredResource.resource) == 0)
            {
                resourceMap[pair.first]->requiredResources.erase(resourceMap[pair.first]->requiredResources.begin() + i);
                i--;
            }
            else if (displayMap.count(requiredResource.resource) == 0)
                addNewDisplayNodeFrom(pair.first, requiredResource.resource);
            else if (displayMap[pair.first]->outgoingArrows.count(requiredResource.resource) == 0)
            {
                addDisplayNodeConnection(pair.first, requiredResource.resource);
            }
        }
    }
    for (size_t i = 0; i < listText.size(); i++)
    {
        Game::Instance().RemoveEntity(listText[i], "ResourceMenuState");
        delete listText[i];
    }
    listText.resize(0);
    listLines = 0;
    std::map<string, TraversalInfo> traversalMap;
    for (auto const& pair : resourceMap)
    {
        for (auto& kv : traversalMap)
        {
            kv.second.visited = false;
        }
        createNewListText(pair.first, pair.second, traversalMap);
    }
    if (listLines > maxNonScrollListLines)
    {
        scrollArea->enabled = true;
        scrollBar->enabled = true;
        for (int i = 0; i < 3; i++)
        {
            if (scrollBarVariations[i].minNumberItems <= listLines)
            {
                scrollBar->ResizeScrollBar(scrollBarVariations[i].texture, scrollBarVariations[i].maxScrollHeight);
                break;
            }
        }
    }
}

void ResourceManager::createNewListText(std::string name, Resource* resource, std::map<string, TraversalInfo>& traversalMap)
{
    std::string nameText = name;
    float x = 10;
    float y = 150 + float(listLines) * textHeight;
    int nameWidth = 155;
    int amountWidth = 60;
    SDL_Color textColor = {0, 0, 0};
    bool selected = displayMap[name]->selected;
    if (selected)
    {
        textColor = { 255, 255, 255 };
    }
    addResourceListText(new ResourceListText(x, y, 1, nameText, resource->name, 23, textColor, Assets::Instance().font_Body, 10, 4, false, selected));
    listLines++;
    size_t maxAmountSize = 4;
    std::string amountText = "x" + std::to_string(resource->amount);
    if (amountText.size() > maxAmountSize)
    {
        amountText = "99+";
    }
    addResourceListText(new ResourceListText(x + nameWidth, y, 1, amountText, resource->name, 23, textColor, Assets::Instance().font_Body, 4, 4, false, selected));
    DisplayNode* currNode = displayMap[name];
    bool craftable = false;
    bool visible = false;
    determineResourceStatus(*resource, traversalMap, visible, craftable);
    if (visible)
    {
        for (auto& targetArrow : currNode->outgoingArrows)
        {
            targetArrow.second->enabled = true;
        }
        currNode->enabled = true;
    }
    else
    {
        for (auto& targetArrow : currNode->outgoingArrows)
        {
            targetArrow.second->enabled = false;
        }
        currNode->enabled = false;
    }
    currNode->displayCraftButton = craftable;
    std::string craftText;
    if (craftable)
    {
        craftText = "craftable";
    }
    else
    {
        craftText = "can't craft";
    }
    addResourceListText(new ResourceListText(x + nameWidth + amountWidth, y, 1, craftText, resource->name, 23, textColor, Assets::Instance().font_Body, 11, 4, false, selected));
    y = 150 + float(listLines) * textHeight;
    if (displayMap[name]->selected)
    {
        if (resource->requiredResources.size() > 0)
        {
            addResourceListText(new ResourceListText(x, y, 1, "Requires:", resource->name, 23, textColor, Assets::Instance().font_Body, 25, 4, true, selected));
            for (size_t i = 0; i < resource->requiredResources.size(); i++)
            {
                y += textHeight;
                listLines++;
                std::string text = resource->requiredResources[i].resource + " x" + std::to_string(resource->requiredResources[i].amount);
                addResourceListText(new ResourceListText(x, y, 1, text, resource->name, 23, textColor, Assets::Instance().font_Body, 25, 4, true, selected));
            }
            listLines++;
        }
    }
}

void ResourceManager::addResourceListText(ResourceListText* text)
{
    Game::Instance().AddEntity(text, "ResourceMenuState");
    listText.push_back(text);
}

//a resource is visible in the visual graph if there is one or more of it OR if it is craftable
void ResourceManager::determineResourceStatus(Resource& resource, std::map<string, TraversalInfo>& traversalMap, bool& visible, bool& craftable)
{
    //More than one of resource in graph
    if (resource.amount > 0)
    {
        visible = true;
    }
    craftable = isImmediatelyCraftable(resource);
    if (!visible)
        visible = isCraftable(resource, traversalMap);
}

struct ResourcePath
{
    ResourceAmount resourceAmount;
    std::vector<std::string> path;

    ResourcePath(std::string resource, int amount)
    {
        this->resourceAmount = ResourceAmount(resource, amount);
    }

    ResourcePath(std::string resource, int amount, std::vector<string> path)
    {
        this->path = path;
        this->resourceAmount = ResourceAmount(resource, amount);
    }
};

bool ResourceManager::isImmediatelyCraftable(Resource& resource)
{
    if (resource.requiredResources.size() == 0) return false;
    for (size_t i = 0; i < resource.requiredResources.size(); i++)
    {
        if (resource.requiredResources[i].amount > resourceMap[resource.requiredResources[i].resource]->amount)
        {
            return false;
        }
    }
    return true;
}

//a resource is craftable if all of its required resources exist in the resource map or can be crafted
bool ResourceManager::isCraftable(Resource& resource, std::map<string, TraversalInfo>& traversalMap)
{
    if (resource.requiredResources.size() == 0) return false;
    //need copy of resourceMap to modify amount of resources
    std::map<string, Resource> currResourceMap;
    for (auto& kv : resourceMap)
    {
        currResourceMap[kv.first] = *kv.second;
    }
    stack<ResourcePath> resourceStack;
    for (size_t i = 0; i < resource.requiredResources.size(); i++)
    {
        resourceStack.push(ResourcePath(resource.requiredResources[i].resource, 1));
    }
    while (!resourceStack.empty())
    {
        ResourcePath topResourcePath = resourceStack.top();
        Resource topResource = currResourceMap[topResourcePath.resourceAmount.resource];
        resourceStack.pop();
        //enough of required resource
        if (topResource.amount >= topResourcePath.resourceAmount.amount)
        {
            continue;
        }
        //check to see if amount obtainable is known and sufficient
        //and check to see if cycle exists
        if (traversalMap[topResource.name].amountObtainable != -1
            && traversalMap[topResource.name].amountObtainable < topResourcePath.resourceAmount.amount)
        {
            return false;
        }
        if (traversalMap[topResource.name].amountObtainable >= topResourcePath.resourceAmount.amount)
            continue;
        for (size_t i = 0; i < topResourcePath.path.size(); i++)
        {
            if (topResourcePath.path[i] == topResource.name)
            {
                return false;
            }
        }
        if (topResource.requiredResources.size() == 0)
        {
            traversalMap[resource.name].amountObtainable = 0;
            return false;
        }
        for (size_t i = 0; i < topResource.requiredResources.size(); i++)
        {
            //if erase was called on resource remove it from required resources since it no longer exists
            if (currResourceMap.count(topResource.requiredResources[i].resource) == 0)
            {
                resourceMap[topResource.name]->requiredResources.erase(topResource.requiredResources.begin() + i);
                currResourceMap[topResource.name].requiredResources.erase(topResource.requiredResources.begin() + i);
                i--;
                continue;
            }
            //only push resource on to stack if there aren't enough of it currently
            int amountNeeded = topResource.requiredResources[i].amount * topResourcePath.resourceAmount.amount;
            int amountCurrent = currResourceMap[topResource.requiredResources[i].resource].amount;
            //not enough of required resource on hand see if required resource can be crafted
            if (amountNeeded > amountCurrent)
            {
                currResourceMap[topResource.requiredResources[i].resource].amount = 0;
                std::vector<std::string> newPath = topResourcePath.path;
                newPath.push_back(topResource.name);
                resourceStack.push(ResourcePath(topResource.requiredResources[i].resource, amountNeeded - amountCurrent, newPath));
            }
            //enough of required resource on hand deduct amount of required resource currently held since it is being used to craft top resource
            else
            {
                currResourceMap[topResource.requiredResources[i].resource].amount -= amountNeeded;
            }
        }
    }
    return true;
}

void ResourceManager::updateSelectedText()
{
    //remove old selected text
    int linesDeleted = 0;
    for (size_t i = 0; i < listText.size(); i++)
    {
        //text corresponds to previously selected node
        if (listText[i]->selected && !displayMap[listText[i]->name]->selected)
        {
            //remove text
            if (listText[i]->requirment)
            {
                linesDeleted++;
                listLines--;
                ResourceListText* deleted = listText[i];
                Game::Instance().RemoveEntity(deleted, "ResourceMenuState");
                listText.erase(listText.begin() + i);
                delete deleted;
                i--;
            }
            //change text color
            else
            {
                listText[i]->updateColor({ 0, 0 ,0 });
                listText[i]->selected = false;
            }
        }
        //text should move up by number of lines deleted
        else
        {
            listText[i]->pos.y -= linesDeleted * textHeight;
        }
    }
    int linesAdded = 0;
    //add new selected text
    for (size_t i = 0; i < listText.size(); i++)
    {
        //text corresponds to previously selected node
        if (!listText[i]->selected && displayMap[listText[i]->name]->selected)
        {
            listText[i]->selected = true;
            listText[i]->updateColor({ 255, 255 ,255 });
            float y = listText[i]->pos.y;
            float x = listText[i]->pos.x;
            if (linesAdded == 0 )
            {
                scrollBar->scrollTo(y/4);
                if (resourceMap[listText[i]->name]->requiredResources.size() > 0)
                {
                    linesAdded++;
                    y += textHeight;
                    listLines++;
                    std::string text = "Requires:";
                    ResourceListText* requirementText = new ResourceListText(x, y, 1, text, listText[i]->name, 23, { 255,255,255 }, Assets::Instance().font_Body, 25, 4, true, true);
                    listText.emplace(listText.begin() + i, requirementText);
                    Game::Instance().AddEntity(requirementText, "ResourceMenuState");
                    i++;
                    for (auto& entry : resourceMap[listText[i]->name]->requiredResources)
                    {
                        linesAdded++;
                        y += textHeight;
                        listLines++;
                        std::string text = entry.resource + " x" + std::to_string(entry.amount);
                        ResourceListText* requirementText = new ResourceListText(x, y, 1, text, listText[i]->name, 23, { 255,255,255 }, Assets::Instance().font_Body, 25, 4, true, true);
                        listText.emplace(listText.begin() + i, requirementText);
                        Game::Instance().AddEntity(requirementText, "ResourceMenuState");
                        i++;
                    }
                }
            }
        }
        //text should move up by number of lines deleted
        else
        {
            listText[i]->pos.y += linesAdded * textHeight;
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
        if (pair.second->requiredResources.size() == 0) continue;
        file << pair.first;
        for (size_t i = 0; i < pair.second->requiredResources.size(); i++)
        {
            if (pair.second->requiredResources[i].amount > 1)
            {
                file << " " + pair.second->requiredResources[i].resource << "[" << pair.second->requiredResources[i].amount << "]";
            }
            else
            {
                file << " " + pair.second->requiredResources[i].resource;
            }
        }
        file << std::endl;
    }
    file.close();
}

float ResourceManager::getMaxTextOffset()
{
    return static_cast<float>((listLines - maxNonScrollListLines) * textHeight);
}

void ResourceManager::addNewDisplayNode(std::string name, int amount)
{
    Vector2 newPos(-24, -24);
    //make newpos opposite to average pos
    if (displayMap.size() > 0)
    {
        newPos.x = 0;
        newPos.y = 0;
        for (auto const& pair : displayMap)
        {
            newPos += pair.second->pos;
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
    DisplayNode* displayNode = new DisplayNode(newPos.x, newPos.y, 4, Assets::Instance().img_circleNode, 2, name, amount, 15);
    displayMap[name] = displayNode;
    Game::Instance().AddEntity(displayNode, "ResourceMenuState");
}

void ResourceManager::addNewDisplayNodeFrom(std::string from, std::string name)
{
    Vector2 minOffset(-24, -24);
    Vector2 maxOffset(24, 24);
    DisplayNode* fromNode = displayMap[from];
    Vector2 newPos(0, 0);
    if (fromNode->points.size() > 0)
    {
        for (size_t i = 0; i < fromNode->points.size(); i++)
        {
            newPos += fromNode->points[i];
        }
        newPos /= -float(fromNode->points.size());
        newPos += fromNode->pos;
    }
    else
    {
        newPos.x = fromNode->pos.x + 64;
        newPos.y = fromNode->pos.y;
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
    DisplayNode* displayNode = new DisplayNode(newPos.x, newPos.y, 4, Assets::Instance().img_circleNode, 2, name, 0, 15);
    displayMap[name] = displayNode;
    Game::Instance().AddEntity(displayNode, "ResourceMenuState");
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
    Vector2 arrowStart = Vector2(fromPos.x + fromOffset.x, fromPos.y + fromOffset.y);
    Vector2 arrowEnd = Vector2(toPos.x + toOffset.x, toPos.y + toOffset.y);
    ArrowEntity* arrow = new ArrowEntity(arrowStart, arrowEnd, 4, NULL, 2);
    fromNode->outgoingArrows[to] = arrow;
    fromNode->points.push_back(fromOffset);
    toNode->points.push_back(toOffset);
    Game::Instance().AddEntity(arrow, "ResourceMenuState");
}

bool ResourceManager::noOverlap(Vector2 pos)
{
    for (auto const& pair : displayMap)
    {
        if (pos.distance(pair.second->pos) <= 64)
            return false;
    }
    return true;
}

DisplayNode* ResourceManager::getSelectedDisplayNode(Vector2 mousePos)
{
    DisplayNode* selected = NULL;
    for (auto const& pair : displayMap)
    {
        pair.second->selected = false;
        if (!pair.second->enabled) continue;
        Vector2 nodeScreenPos = pair.second->getCenterPos() * pair.second->scale / 4 + pair.second->viewportCenter;
        if (nodeScreenPos.distance(mousePos) < pair.second->size.x / 2 * pair.second->scale / 4 && !pair.second->posInCraftButton(mousePos))
        {
            selected = pair.second;
            pair.second->selected = true;
        }
    }
    return selected;
}

ResourceManager::~ResourceManager()
{
    for (auto const& pair : resourceMap)
    {
        delete pair.second;
    }
}

ResourceManager::ResourceManager() 
{
    scrollArea = nullptr;
    scrollBar = nullptr;
}
