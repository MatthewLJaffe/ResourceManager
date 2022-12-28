#pragma once
#include <string>
#include "Utils.hpp"
#include <Vector>
#include "Resource.hpp"
#include "TextEntity.hpp"
#include "Assets.hpp"

class ResourceManager
{
public:
	ResourceManager(const ResourceManager&) = delete;
	static ResourceManager& Instance();
	void addResource(std::string line);
	void deleteResource(std::string resource, std::vector<TextEntity*> &resourceList);
	void addNode(std::string node, std::vector<TextEntity*> &resourceList);
	void addLink(std::string from, string to, std::vector<TextEntity*> &resourceList);
	bool isCraftable(Resource& resource);
	void displayGraph(std::vector<TextEntity*> &resourceList);
	void outputGraph(std::string name);
private:
	ResourceManager();
	map<string, Resource*> resourceMap;

};