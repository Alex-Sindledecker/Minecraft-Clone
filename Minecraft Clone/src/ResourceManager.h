#pragma once

#include <unordered_map>
#include <string>

class Resource
{
public:
	virtual ~Resource() {}
	virtual void init(const char* src) 
	{
		was_initalized = true;
	};

	bool was_initalized;
};

typedef std::shared_ptr<Resource> ResourcePtr;

class ResourceManager
{
public:
	static ResourcePtr get(std::string name);
	static void del(std::string name);

private:
	ResourceManager() {}
	ResourceManager(const ResourceManager&) {}
	~ResourceManager() {}

	static std::unordered_map<std::string, ResourcePtr> resources;
};

