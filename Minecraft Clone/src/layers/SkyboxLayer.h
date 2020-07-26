#pragma once

#include "game/Settings.h"
#include "Layer.h"
#include "ResourceManager.h"
#include "game/Camera.h"

class SkyboxLayer : public Layer
{
public:
	virtual void onCreate() override;
	virtual void onUpdate(float dt) override;
	virtual void onRender() override;

private:
	ShaderPtr skybox_shader;
	VertexArrayPtr skybox_mesh;
	Texture3DPtr skybox_cubemap;
	PerspectiveCamera camera;
	float sensitivity, camera_speed;

	glm::mat4 model;
};