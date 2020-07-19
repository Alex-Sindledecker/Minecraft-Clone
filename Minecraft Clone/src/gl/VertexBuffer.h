#pragma once

#include "glad/glad.h"

class VertexBuffer
{
public:
	VertexBuffer() {}
	VertexBuffer(const void* data, size_t size, GLenum type = GL_ARRAY_BUFFER);
	~VertexBuffer();

	void init(const void* data, size_t size, GLenum type = GL_ARRAY_BUFFER);
	void bind() const;
	void unbind() const;

private:
	GLuint m_id;
	GLenum m_type;
};