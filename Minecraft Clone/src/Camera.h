#pragma once

#include "Transformable.h"

class PerspectiveCamera : public Transformable
{
public:
	PerspectiveCamera(float fov, float aspect_ratio, glm::vec3 pos);
	PerspectiveCamera();
	~PerspectiveCamera();

	void lookVertically(float d);
	void lookHorizontally(float d);
	void zoom(float dist);
	void setAspectRatio(float aspect_ratio);
	void setViewRange(float near_plane, float far_plane);
	void computeDirectionVectors();
	glm::mat4 getViewProjectionTransform();
	glm::vec3 getViewDirection() const;
	glm::vec3 getRight() const;

private:
	glm::vec3 m_pry; //Pitch roll yaw
	glm::vec3 m_view_dir, m_right, m_up;
	float m_fov;
	float m_aspect_ratio;
	float m_near;
	float m_far;
};