#include "pch.h"
#include "Texture.h"

#include <stb_image.h>

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
}

void Texture2D::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture2D::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::init(const char* src)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int channels, width, height;
	unsigned char* pixels = stbi_load(src, &width, &height, &channels, NULL);
	if (pixels == NULL)
	{
		CONSOLE_LOG_ERROR("Texture.cpp", "Failed to load image from " << src);
		unbind();
		return;
	}
	GLenum format = GL_RED;
	switch (channels)
	{
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	case 1:
		format = GL_RED;
		break;
	case 2:
		format = GL_RG;
		break;
	}
	glTexImage2D(GL_TEXTURE_2D, 8, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
	stbi_image_free(pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture3D::Texture3D()
{
}

Texture3D::~Texture3D()
{
}
