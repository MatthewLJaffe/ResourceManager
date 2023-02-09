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


/// <summary>
/// used to help determine which resources are displayable and craftable
/// </summary>
struct TraversalInfo
{
	int amountObtainable;
	bool visited;
	TraversalInfo();
};

/// <summary>
/// encapsulation of what scroll bar size to display for what amount of items in the resource text list
/// </summary>
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
	/// <summary>
	/// checks for craft button press to determine if resource should be crafted
	/// </summary>
	/// <param name="mousePos"></param>
	void checkCraftButtonPressed(Vector2 mousePos);
	/// <summary>
	/// initializes resource from line of provided text file
	/// </summary>
	/// <param name="line"></param>
	/// <param name="startWithResource"></param>
	void addResource(std::string line, bool startWithResource);
	/// <summary>
	/// reduces the amount of a resource
	/// </summary>
	/// <param name="resource">resource to delete</param>
	void deleteResource(std::string resource);
	/// <summary>
	/// adds a node in the resource graph creating a new resource if one does not already exist
	/// </summary>
	/// <param name="node"></param>
	void addNode(std::string node);
	void addLink(std::string from, string to);
	/// <summary>
	/// adds a link between nodes in the display graph
	/// </summary>
	/// <param name="from">node that requires to</param>
	/// <param name="to">node that is required for from to be crafted</param>
	void unLink(std::string from, string to);
	/// <summary>
	/// completely removes node from display graph resources that depended on that node to be crafted no longer do
	/// </summary>
	/// <param name="resource">resourec to remove</param>
	void erase(std::string resource);
	void craftResource(std::string resource);
	/// <summary>
	/// resets resource counts for start of a new game
	/// </summary>
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