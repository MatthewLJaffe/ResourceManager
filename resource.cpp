#include "Resource.hpp"

Resource::Resource(std::string name)
{
    this->name = name;
    this->active = true;
}

Resource::Resource(std::string name, std::vector<std::string> requiredResources)
{
    this->name = name;
    this->requiredResources = requiredResources;
    this->active = true;
}


