#include "pch.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, size_t size, GLenum type)
{
	m_type = type;
	glGenBuffers(1, &m_id);
	bind();
	glBufferData(m_type, size, data, GL_STATIC_DRAW);
	unbind();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void VertexBuffer::init(const void* data, size_t size, GLenum type)
{
	m_type = type;
	glGenBuffers(1, &m_id);
	bind();
	glBufferData(m_type, size, data, GL_STATIC_DRAW);
	unbind();
}

void VertexBuffer::bind() const
{
	glBindBuffer(m_type, m_id);
}

void VertexBuffer::unbind() const
{
	glBindBuffer(m_type, 0);
}
