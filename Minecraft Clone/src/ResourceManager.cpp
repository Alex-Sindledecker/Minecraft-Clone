#include "pch.h"
#include "ResourceManager.h"

std::unordered_map<std::string, ShaderPtr> ResourceManager::shaders;

ShaderPtr ResourceManager::getShader(std::string name)
{
	if (shaders.find(name) == shaders.end())
	{
		shaders[name] = ShaderPtr(new Shader);
	}

	return shaders[name];
}
