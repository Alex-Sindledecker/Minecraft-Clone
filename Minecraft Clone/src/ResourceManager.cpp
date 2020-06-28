#include "pch.h"
#include "ResourceManager.h"

std::unordered_map<std::string, ResourcePtr> ResourceManager::resources;

ResourcePtr ResourceManager::get(std::string name)
{
	if (resources.find(name) == resources.end())
	{
		resources[name] = ResourcePtr(new Resource);
		resources[name]->was_initalized = false;
	}

	return resources[name];
}

void ResourceManager::del(std::string name)
{
	resources.erase(name);
}
