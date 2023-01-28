#pragma once
#include <string>
#include "Utils.hpp"
#include <Vector>
#include "Resource.hpp"
#include "ResourceListText.hpp"
#include "Assets.hpp"
#include "ScrollBar.hpp"
#include "Game.hpp"
#include "DisplayNode.hpp"
#include <stack>

class ScrollBar;
class DisplayNode;



struct TraversalInfo
{
	int amountObtainable;
	bool visited;
	TraversalInfo();
};


struct ScrollBarVariation
{
	ScrollBarVariation(SDL_Texture* tex, int maxScrollHeight, int minNumberItems);
	int maxScrollHeight;
	SDL_Texture* texture;
	int minNumberItems;
};

class ResourceManager
{
public:
	ResourceManager(const ResourceManager&) = delete;
	static ResourceManager& Instance();
	int maxNonScrollListLines = 14;
	int textHeight = 40;
	ScrollBar* scrollBar;
	Entity* scrollArea;
	std::map<string, Resource*> resourceMap;
	DisplayNode* getSelectedDisplayNode(Vector2 mousePos);
	void init(ScrollBar* scrollBar, Entity* scrollArea);
	void checkCraftButtonPressed(Vector2 mousePos);
	void addResource(std::string line, bool startWithResource);
	void deleteResource(std::string resource);
	void addNode(std::string node);
	void addLink(std::string from, string to);
	void unLink(std::string from, string to);
	void erase(std::string resource);
	void craftResource(std::string resource);
	void resetResources();
	void addNewDisplayNode(std::string name, int amount);
	void setResourceAmount(std::string resource, int amount);
	void addNewDisplayNodeFrom(std::string from, std::string name);
	void addDisplayNodeConnection(std::string from, std::string to);
	void createNewListText(std::string name, Resource* resource, std::map<string, TraversalInfo>& traversalMap);
	void addResourceListText(ResourceListText* text);
	void updateSelectedText();
	void displayGraph();
	float getMaxTextOffset();
	void outputGraph(std::string name);
	std::map<string, DisplayNode*> displayMap;
private:
	int listLines = 0;
	void determineResourceStatus(Resource& resource, std::map<string, TraversalInfo>& visitedMap, bool& isVisible, bool& isCraftable);
	bool isCraftable(Resource& resource, std::map<string, TraversalInfo>& visitedMap);
	bool noOverlap(Vector2 pos);
	bool isImmediatelyCraftable(Resource& resource);
	ScrollBarVariation scrollBarVariations[3] = { {NULL, 161, 21}, {NULL, 113, 18}, {NULL, 49, 15}};
	ResourceManager();
	std::vector<ResourceListText*> listText;
	~ResourceManager();
};