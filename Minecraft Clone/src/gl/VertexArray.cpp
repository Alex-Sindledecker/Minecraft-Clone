#include "pch.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
	m_index_buffer = nullptr;
	m_slot = 0;
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_id);
	if (m_index_buffer != nullptr)
	{
		m_index_buffer->bind();
	}
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
	if (m_index_buffer != nullptr)
	{
		m_index_buffer->unbind();
	}
}

void VertexArray::setIndexBufer(VertexBuffer* buffer)
{
	m_index_buffer = buffer;
}