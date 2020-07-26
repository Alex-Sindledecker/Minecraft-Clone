#include "pch.h"
#include "NoiseTestingLayer.h"
#include "world/terrain/TerrainGenerator.h"

float verts[] = 
{
	-1.0, -1.0,
	 1.0, -1.0,
	 1.0,  1.0,
	 1.0,  1.0,
	-1.0,  1.0,
	-1.0, -1.0
};

unsigned char getNoise(FastNoise& noise, float x, float y)
{
	if (x <= 1920 / 2 - 200)
	{
		noise.SetFrequency(0.1);
		return (noise.GetSimplex(x, y) + 1.f) / 2.f * 255.f;
	}
	else if (x >= 1920 / 2 + 200)
	{
		noise.SetFrequency(0.01);
		return (noise.GetSimplex(x, y) + 1.f) / 2.f * 255.f;
	}
	else
	{
		noise.SetFrequency(0.1);
		float val1 = noise.GetSimplex(x, y);
		noise.SetFrequency(0.01);
		float val2 = noise.GetSimplex(x, y);
		float d = (x - (1920.f / 2.f - 200.f)) / 400.f;
		noise.SetFrequency(0.1 + d * (0.01 - 0.1));
		float val3 = noise.GetSimplex(x, y);
		return ((val1 + val2) / 2.f + 1.f) / 2.f * 255.f;

		//float d = (x - (1920.f / 2.f - 200.f)) / 400.f;
		//noise.SetFrequency(0.1 + d * (0.01 - 0.1));
		//return (noise.GetSimplex(x, y) + 1.f) / 2.f * 255.f;
	}
}

#include <time.h>
void NoiseTestingLayer::onCreate()
{
	VertexBufferPtr vbo = ResourceManager::getVertexBuffer("quad_vbo");
	vbo->init(verts, sizeof(verts));

	vao = ResourceManager::getVertexArray("quad_vao");
	vao->bind();
	vao->push<float>(*vbo.get(), 2, 0);
	vao->unbind();

	shader = ResourceManager::getShader("quad_shader");
	shader->init("res/shaders/quad_vertex.glsl", "res/shaders/quad_fragment.glsl");
	
	TerrainGenerator gen(256);

	unsigned char* pixels = new unsigned char[1080 * 1920];
	for (int y = 0; y < 1080; y++)
	{
		for (int x = 0; x < 1920; x++)
		{
			Block this_block = gen.getBlock(x, 15, y);
			if (this_block.id != BlockType::AIR)
				pixels[y * 1920 + x] = 0;
			else
				pixels[y * 1920 + x] = 1;
		}
	}
	tex = ResourceManager::getTexture2D("noise_texture");
	tex->init(pixels, 1920, 1080, 1);
	delete[] pixels;
}

void NoiseTestingLayer::onUpdate(float dt)
{
}

void NoiseTestingLayer::onRender()
{
	shader->use();
	tex->bind();
	vao->bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	vao->unbind();
	tex->unbind();
}
