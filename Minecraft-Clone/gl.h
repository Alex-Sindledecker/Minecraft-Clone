//Contains opengl functionality

#pragma once

#include <glad/glad.h>
#include <vector>

namespace gl
{
	typedef GLuint ShaderProgram, Shader;
	typedef GLuint Buffer, VertexArray;

	struct VertexAttribute
	{
		void* offset;
		unsigned int elements;
		unsigned int divisor;
		Buffer buffer;
		GLsizei stride;
		GLenum dataType, bufferType;
	};

	//Initializes opengl
	int init(GLADloadproc proc);
	ShaderProgram loadShader(const char* vertexPath, const char* fragmentPath);
	Shader loadShaderModule(const char* path, GLenum type);

	Buffer createBuffer(GLenum bufferType, void* bufferData, size_t bufferSize, GLenum access);
	VertexArray createVertexArray(const std::vector<VertexAttribute>& attributes);
	VertexArray createVertexArray(const std::vector<VertexAttribute>& attributes, Buffer elementBuffer);

	void enableWireframeDraw();
	void disableWireframeDraw();
	void drawArrays(VertexArray vao, unsigned int vertexCount);
	void drawElements(VertexArray vao, unsigned int elementCount);
}