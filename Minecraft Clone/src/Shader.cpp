#include "pch.h"
#include "Shader.h"
#include "toolbox.h"

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::init(const char* vertex_src, const char* fragment_src)
{
	std::string vertex_content = toolbox::readFile(vertex_src);
	std::string fragment_content = toolbox::readFile(fragment_src);
	const char* vertex_cstr = vertex_content.c_str();
	const char* fragment_cstr = fragment_content.c_str();

	GLuint vertex = genShaderComponent(vertex_src, GL_VERTEX_SHADER);
	GLuint fragment = genShaderComponent(fragment_src, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	glDetachShader(id, vertex);
	glDetachShader(id, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::setUniformMatrix4(const char* location, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(id, location), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniformVector4(const char* location, glm::vec4 vector)
{
	glUniform4fv(glGetUniformLocation(id, location), 1, &vector[0]);
}

void Shader::setUniformVector3(const char* location, glm::vec3 vector)
{
	glUniform3fv(glGetUniformLocation(id, location), 1, &vector[0]);
}

void Shader::setUniformFloat(const char* location, float value)
{
	glUniform1f(glGetUniformLocation(id, location), value);
}

void Shader::setUniformInt(const char* location, int value)
{
	glUniform1i(glGetUniformLocation(id, location), value);
}

GLuint Shader::genShaderComponent(const char* src, GLenum type)
{
	std::string shader_content = toolbox::readFile(src);
	const char* shader_cstr = shader_content.c_str();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &shader_cstr, NULL);
	glCompileShader(shader);

	#ifdef _DEBUG
		int status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			char infolog[512];
			glGetShaderInfoLog(shader, sizeof(infolog), NULL, infolog);
			std::cout << infolog << std::endl;
		}
	#endif

	return shader;
}
