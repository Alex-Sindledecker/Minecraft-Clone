#pragma once

#include <unordered_map>
#include <string>

#include "Shader.h"

typedef std::shared_ptr<Shader> ShaderPtr;

class ResourceManager
{
public:
	static ShaderPtr getShader(std::string name);

private:
	ResourceManager() {}
	ResourceManager(const ResourceManager&) {}
	~ResourceManager() {}

	static std::unordered_map<std::string, ShaderPtr> shaders;
};