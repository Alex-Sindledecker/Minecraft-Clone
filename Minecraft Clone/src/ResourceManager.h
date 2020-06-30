#pragma once

#include <unordered_map>
#include <string>

#include "Shader.h"
#include "Texture.h"

typedef std::shared_ptr<Shader> ShaderPtr;
typedef std::shared_ptr<Texture> TexturePtr;
typedef std::shared_ptr<Texture2D> Texture2DPtr;
typedef std::shared_ptr<Texture3D> Texture3DPtr;

class ResourceManager
{
public:
	static ShaderPtr getShader(std::string name);
	static Texture2DPtr getTexture2D(std::string name);
	static Texture3DPtr getTexture3D(std::string name);

private:
	ResourceManager() {}
	ResourceManager(const ResourceManager&) {}
	~ResourceManager() {}

	static std::unordered_map<std::string, ShaderPtr> m_shaders;
	static std::unordered_map<std::string, Texture2DPtr> m_textures2;
	static std::unordered_map<std::string, Texture3DPtr> m_textures3;
};