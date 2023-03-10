#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

struct ResourceAmount
{
	//current amount of resource collected
	int amount;
	//name of resource
	std::string resource;
	ResourceAmount(std::string resource, int amount);
	ResourceAmount();
};

class Resource
{
public:
	std::vector<ResourceAmount> requiredResources;
	std::string name;
	int amount = 0;
    Resource(std::string name);
	Resource(std::string name, std::vector<ResourceAmount> requiredResources);
	Resource();
};