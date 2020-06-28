#include "pch.h"
#include "ResourceManager.h"

std::unordered_map<std::string, ShaderPtr> ResourceManager::shaders;
std::unordered_map<std::string, Texture2DPtr> ResourceManager::textures2;
std::unordered_map<std::string, Texture3DPtr> ResourceManager::textures3;

ShaderPtr ResourceManager::getShader(std::string name)
{
	if (shaders.find(name) == shaders.end())
	{
		shaders[name] = ShaderPtr(new Shader);
	}

	return shaders[name];
}

Texture2DPtr ResourceManager::getTexture2D(std::string name)
{
	if (textures2.find(name) == textures2.end())
	{
		textures2[name] = Texture2DPtr(new Texture2D);
	}

	return textures2[name];
}

Texture3DPtr ResourceManager::getTexture3D(std::string name)
{
	if (textures3.find(name) == textures3.end())
	{
		textures3[name] = Texture3DPtr(new Texture3D);
	}

	return textures3[name];
}
