//Contains opengl functionality

#include "gl.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace gl
{
	static int statusSuccess;
	static char statusInfoLog[512];

	int init(GLADloadproc proc)
	{
		if (!gladLoadGLLoader(proc))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		glEnable(GL_DEPTH_TEST);
	}

	ShaderProgram loadShader(const char* vertexPath, const char* fragmentPath)
	{
		Shader vertexShader = loadShaderModule(vertexPath, GL_VERTEX_SHADER);
		Shader fragmentShader = loadShaderModule(fragmentPath, GL_FRAGMENT_SHADER);

		ShaderProgram shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		// Check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &statusSuccess);
		if (!statusSuccess) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, statusInfoLog);
			std::cout << "Shader linkage failed!\nVertexPath: " << vertexPath << "\nFragment Path: " << fragmentPath << "\n\n" << statusInfoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgram;
	}

	Shader loadShaderModule(const char* path, GLenum type)
	{
		std::ifstream file(path);
		if (file.is_open())
		{
			//Read file into string
			std::stringstream ss;
			ss << file.rdbuf();
			std::string str = ss.str();
			
			const char* cstr = str.c_str(); //Get c string format
			
			//Create shader
			Shader shader = glCreateShader(type);
			glShaderSource(shader, 1, &cstr, NULL);
			glCompileShader(shader);

			//Check for compile errors
			glGetShaderiv(shader, GL_COMPILE_STATUS, &statusSuccess);
			if (!statusSuccess)
			{
				glGetShaderInfoLog(shader, 512, NULL, statusInfoLog);
				std::cout << "Shader Compilation Failed!\nShader Path: " << path << "\n\n" << statusInfoLog << std::endl;
			}

			return shader;
		}
		else
		{
			std::cout << "Failed to load shader from " << path << "!\n" << std::endl;
			return -1;
		}
	}

	Buffer createBuffer(GLenum bufferType, void* bufferData, size_t bufferSize, GLenum access)
	{
		Buffer vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(bufferType, vbo);
		glBufferData(bufferType, bufferSize, bufferData, access);
		glBindBuffer(bufferType, 0);

		return vbo;
	}

	VertexArray createVertexArray(const std::vector<VertexAttribute>& attributes)
	{
		VertexArray vao;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		for (int i = 0; i < attributes.size(); i++)
		{
			const VertexAttribute& att = attributes[i];

			glBindBuffer(att.bufferType, att.buffer);

			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, att.elements, att.dataType, GL_FALSE, att.stride, att.offset);
			glVertexAttribDivisor(i, att.divisor);
		}

		glBindVertexArray(0);

		return vao;
	}

	VertexArray createVertexArray(const std::vector<VertexAttribute>& attributes, Buffer elementBuffer)
	{
		VertexArray vao;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

		for (int i = 0; i < attributes.size(); i++)
		{
			const VertexAttribute& att = attributes[i];

			glBindBuffer(att.bufferType, att.buffer);

			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, att.elements, att.dataType, GL_FALSE, att.stride, att.offset);
			glVertexAttribDivisor(i, att.divisor);
		}

		glBindVertexArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return vao;
	}

	void enableWireframeDraw()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void disableWireframeDraw()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void drawArrays(VertexArray vao, unsigned int vertexCount)
	{
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	}

	void drawElements(VertexArray vao, unsigned int elementCount)
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, NULL);
	}

}