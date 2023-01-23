#include "Resource.hpp"
ResourceAmount::ResourceAmount(std::string resource, int amount)
{
    this->resource = resource;
    this->amount = amount;
}

ResourceAmount::ResourceAmount()
{
    this->resource = "";
    this->amount = 0;
}

Resource::Resource()
{
    this->name = "";
    this->amount = 0;
}

Resource::Resource(std::string name)
{
    this->name = name;
}

Resource::Resource(std::string name, std::vector<ResourceAmount> requiredResources)
{
    this->name = name;
    this->requiredResources = requiredResources;
}


