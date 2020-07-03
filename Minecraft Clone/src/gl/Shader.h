#pragma once

#include <glad/glad.h>

class Shader
{
public:
	Shader() : m_id(0) {}
	~Shader();

	void use();
	void init(const char* vertex_src, const char* fragment_src);
	void setUniformMatrix4(const char* location, glm::mat4 matrix);
	void setUniformVector4(const char* location, glm::vec4 vector);
	void setUniformVector3(const char* location, glm::vec3 vector);
	void setUniformFloat(const char* location, float value);
	void setUniformInt(const char* location, int value);

private:
	GLuint genShaderComponent(const char* src, GLenum type);

	GLuint m_id;
};