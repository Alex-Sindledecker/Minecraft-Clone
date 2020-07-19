#include "pch.h"
#include "ResourceManager.h"

std::unordered_map<std::string, ShaderPtr> ResourceManager::m_shaders;
std::unordered_map<std::string, Texture2DPtr> ResourceManager::m_textures2;
std::unordered_map<std::string, Texture3DPtr> ResourceManager::m_textures3;
std::unordered_map<std::string, VertexArrayPtr> ResourceManager::m_vertex_arrays;
std::unordered_map<std::string, VertexBufferPtr> ResourceManager::m_vertex_buffers;

ShaderPtr ResourceManager::getShader(std::string name)
{
	if (m_shaders.find(name) == m_shaders.end())
	{
		m_shaders[name] = ShaderPtr(new Shader);
	}

	return m_shaders[name];
}

Texture2DPtr ResourceManager::getTexture2D(std::string name)
{
	if (m_textures2.find(name) == m_textures2.end())
	{
		m_textures2[name] = Texture2DPtr(new Texture2D);
	}

	return m_textures2[name];
}

Texture3DPtr ResourceManager::getTexture3D(std::string name)
{
	if (m_textures3.find(name) == m_textures3.end())
	{
		m_textures3[name] = Texture3DPtr(new Texture3D);
	}

	return m_textures3[name];
}

VertexArrayPtr ResourceManager::getVertexArray(std::string name)
{
	if (m_vertex_arrays.find(name) == m_vertex_arrays.end())
	{
		m_vertex_arrays[name] = VertexArrayPtr(new VertexArray);
	}

	return m_vertex_arrays[name];
}

VertexBufferPtr ResourceManager::getVertexBuffer(std::string name)
{
	if (m_vertex_buffers.find(name) == m_vertex_buffers.end())
	{
		m_vertex_buffers[name] = VertexBufferPtr(new VertexBuffer);
	}

	return m_vertex_buffers[name];
}
