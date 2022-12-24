#include "Resource.hpp"

Resource::Resource(std::string name)
{
    this->name = name;
}

Resource::Resource(std::string name, std::vector<std::string> requiredResources)
{
    this->name = name;
    this->requiredResources = requiredResources;
}


