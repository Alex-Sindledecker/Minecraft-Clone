#include "pch.h"
#include "Texture.h"
#include "game/Settings.h"

#include <stb_image.h>

struct Image
{
	unsigned char* pixels;
	int channels, width, height;
	GLenum format;
};

Image loadImage(const char* src)
{
	Image image;
	image.pixels = stbi_load(src, &image.width, &image.height, &image.channels, NULL);
	if (image.pixels == NULL)
	{
		CONSOLE_LOG_ERROR("Texture.cpp", "Failed to load image from " << src);
		return image;
	}
	image.format = GL_RED;
	switch (image.channels)
	{
	case 3:
		image.format = GL_RGB;
		break;
	case 4:
		image.format = GL_RGBA;
		break;
	case 1:
		image.format = GL_RED;
		break;
	case 2:
		image.format = GL_RG;
		break;
	}
	return image;
}

Texture2D::Texture2D()
{
	glGenTextures(1, &m_id);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_id);
}

void Texture2D::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture2D::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::init(const char* src)
{
	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	#ifdef GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
		if (Settings::anisotropic_filtering_level > 0)
		{
			float aniso = 0;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, Settings::Graphics::anisotropic_filtering_level > aniso ? aniso : Settings::Graphics::anisotropic_filtering_level);
		}
	#endif
	Image image = loadImage(src);
	glTexImage2D(GL_TEXTURE_2D, 0, image.format, image.width, image.height, 0, image.format, GL_UNSIGNED_BYTE, image.pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image.pixels);
}

Texture3D::Texture3D()
{
	glGenTextures(1, &m_id);
}

Texture3D::~Texture3D()
{
	glDeleteTextures(1, &m_id);
}

void Texture3D::bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
}

void Texture3D::unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Texture3D::init(const CubemapTextures& textures)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	Image images[6] = 
	{
		loadImage(textures.right),
		loadImage(textures.left),
		loadImage(textures.top),
		loadImage(textures.bottom),
		loadImage(textures.front),
		loadImage(textures.back)
	};
	for (int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, images[i].format, images[i].width, images[i].height, 0, images[i].format, GL_UNSIGNED_BYTE, images[i].pixels);
		stbi_image_free(images[i].pixels);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
