#pragma once

#include <glad/glad.h>

class Texture
{
public:
	virtual ~Texture() = 0 {}
	virtual void bind() = 0;
	virtual void unbind() = 0;

protected:
	GLuint id = 0;
};

class Texture2D : public Texture
{
public:
	Texture2D();
	~Texture2D();

	void bind() override;
	void unbind() override;
	void init(const char* src);
};

class Texture3D : public Texture
{
public:
	Texture3D();
	~Texture3D();

	void bind() override {}
	void unbind() override {}
};