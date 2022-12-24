#pragma once
#include <string>
#include "Utils.hpp"
#include <Vector>
#include "Resource.hpp"

class ResourceManager
{
public:
	ResourceManager(const ResourceManager&) = delete;
	static ResourceManager& Instance();
	void addResource(std::string line);
	void deleteResource(std::string resource);
	void addNode(std::string node);
	void addLink(std::string from, string to);
	bool isCraftable(Resource& resource);
	void displayGraph();
	void outputGraph(std::string name);
private:
	ResourceManager();
	map<string, Resource*> resourceMap;

};