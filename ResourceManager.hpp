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

class ScrollBar;
class DisplayNode;

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
	int maxNonScrollListItems = 14;
	int textHeight = 40;
	ScrollBar* scrollBar;
	Entity* scrollArea;
	DisplayNode* getSelectedDisplayNode(Vector2 mousePos);
	void init(ScrollBar* scrollBar, Entity* scrollArea);
	void addResource(std::string line);
	void deleteResource(std::string resource);
	void addNode(std::string node);
	void addLink(std::string from, string to);
	void addNewDisplayNode(std::string name);
	void addNewDisplayNodeFrom(std::string from, std::string name);
	void addDisplayNodeConnection(std::string from, std::string to);
	bool isCraftable(Resource& resource);
	void displayGraph();
	float getMaxTextOffset();
	void outputGraph(std::string name);
	std::map<string, DisplayNode*> displayMap;
private:
	//small medium large
	bool noOverlap(Vector2 pos);
	ScrollBarVariation scrollBarVariations[3] = { {NULL, 161, 21}, {NULL, 113, 18}, {NULL, 49, 15}};
	ResourceManager();
	std::map<string, Resource*> resourceMap;
	std::vector<ResourceListText*> listText;
	~ResourceManager();

};