#pragma once

#include "VertexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind()const;

	template<class T>
	void push(const VertexBuffer& data, GLuint size, size_t offset)
	{
		static_assert(false, "Invalid type passed to VertexArray::push<T>(...)");
	}

	template<>
	void push<float>(const VertexBuffer& data, GLuint size, size_t offset)
	{
		data.bind();
		glEnableVertexAttribArray(m_slot);
		glVertexAttribPointer(m_slot, size, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)(offset * sizeof(float)));
		data.unbind();
		m_slot++;
	}

	template<>
	void push<unsigned int>(const VertexBuffer& data, GLuint size, size_t offset)
	{
		data.bind();
		glEnableVertexAttribArray(m_slot);
		glVertexAttribIPointer(m_slot, size, GL_UNSIGNED_INT, size * sizeof(unsigned int), (void*)(offset * sizeof(unsigned int)));
		data.unbind();
		m_slot++;
	}

	template<>
	void push<int>(const VertexBuffer& data, GLuint size, size_t offset)
	{
		data.bind();
		glEnableVertexAttribArray(m_slot);
		glVertexAttribIPointer(m_slot, size, GL_FLOAT, size * sizeof(int), (void*)(offset * sizeof(int)));
		data.unbind();
		m_slot++;
	}

private:
	GLuint m_id;
	unsigned int m_slot;
};