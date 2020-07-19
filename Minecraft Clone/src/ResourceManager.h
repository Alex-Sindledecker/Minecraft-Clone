#pragma once

#include <unordered_map>
#include <string>

#include "gl/Shader.h"
#include "gl/Texture.h"
#include "gl/VertexArray.h"

typedef std::shared_ptr<Shader> ShaderPtr;
typedef std::shared_ptr<Texture> TexturePtr;
typedef std::shared_ptr<Texture2D> Texture2DPtr;
typedef std::shared_ptr<Texture3D> Texture3DPtr;
typedef std::shared_ptr<VertexArray> VertexArrayPtr;
typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;

class ResourceManager
{
public:
	static ShaderPtr getShader(std::string name);
	static Texture2DPtr getTexture2D(std::string name);
	static Texture3DPtr getTexture3D(std::string name);
	static VertexArrayPtr getVertexArray(std::string name);
	static VertexBufferPtr getVertexBuffer(std::string name);

private:
	ResourceManager() {}
	ResourceManager(const ResourceManager&) {}
	~ResourceManager() {}

	static std::unordered_map<std::string, ShaderPtr> m_shaders;
	static std::unordered_map<std::string, Texture2DPtr> m_textures2;
	static std::unordered_map<std::string, Texture3DPtr> m_textures3;
	static std::unordered_map<std::string, VertexArrayPtr> m_vertex_arrays;
	static std::unordered_map<std::string, VertexBufferPtr> m_vertex_buffers;
};