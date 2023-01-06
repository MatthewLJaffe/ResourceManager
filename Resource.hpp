#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

class Resource
{
public:
	std::vector<std::string> requiredResources;
	std::string name;
	bool active;
    Resource(std::string name);
	Resource(std::string name, std::vector<std::string> requiredResources);
};

