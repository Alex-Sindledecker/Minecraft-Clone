#pragma once

#include "Layer.h"
#include "ResourceManager.h"

class NoiseTestingLayer : public Layer
{
public:
	virtual void onCreate() override;
	virtual void onUpdate(float dt) override;
	virtual void onRender() override;

private:
	Texture2DPtr tex;
	VertexArrayPtr vao;
	ShaderPtr shader;
};