#pragma once

#include <glm/gtc/matrix_transform.hpp>

class FpsCamera
{
public:
	void update(float dt);
	void updateProjection();
	void updateView();
	glm::mat4 getViewProjection() const;
	glm::vec3 getPos();

private:
	glm::mat4 projection;
	glm::mat4 view;

	glm::vec3 pos = glm::vec3(0, 2, 0), front = glm::vec3(0, 0, 0), up = glm::vec3(0, 1, 0);

	float yaw = 2015.f, pitch = 0.f;
};