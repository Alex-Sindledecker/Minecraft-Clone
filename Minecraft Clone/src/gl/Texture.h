#pragma once

#include <glad/glad.h>

class Texture
{
public:
	virtual ~Texture() = 0 {}
	virtual void bind() = 0;
	virtual void unbind() = 0;

protected:
	GLuint m_id = 0;
};

class Texture2D : public Texture
{
public:
	Texture2D();
	~Texture2D();

	void bind() override;
	void unbind() override;
	void init(const char* src);
	void init(void* pixels, unsigned int width, unsigned int height, unsigned int channels);
};

struct CubemapTextures
{
	const char* top;
	const char* bottom;
	const char* left;
	const char* right;
	const char* front;
	const char* back;
};

class Texture3D : public Texture
{
public:
	Texture3D();
	~Texture3D();

	void bind() override;
	void unbind() override;
	void init(const CubemapTextures& textures);
};