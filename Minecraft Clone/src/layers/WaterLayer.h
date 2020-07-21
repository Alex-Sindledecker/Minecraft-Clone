#pragma once

#include "ResourceManager.h"
#include "Layer.h"

class WaterLayer : public Layer
{
public:
	virtual void onUpdate(float dt) override;

	virtual void onRender() override;

	virtual void onCreate();

private:
	VertexArrayPtr vao;
};