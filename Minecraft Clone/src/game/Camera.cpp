#include "pch.h"
#include "Camera.h"
#include "toolbox.h"

#include <glm/gtc/matrix_transform.hpp>

PerspectiveCamera::PerspectiveCamera(float fov, float aspect_ratio, glm::vec3 pos)
{
	m_fov = fov;
	m_aspect_ratio = aspect_ratio;
	m_pos = pos;
	m_pry = glm::vec3(0, 0, 0);
	m_near = 0.1f;
	m_far = 100.f;
	m_view_dir = glm::vec3(0, 0, 0);
	m_right = glm::vec3(0, 0, 0);
	m_up = glm::vec3(0, 1, 0);
}

PerspectiveCamera::PerspectiveCamera()
{
	m_fov = 70.f;
	m_aspect_ratio = 1.f;
	m_pry = glm::vec3(0, 0, 0);
	m_near = 0.1f;
	m_far = 100.f;
	m_view_dir = glm::vec3(0, 0, 0);
	m_right = glm::vec3(0, 0, 0);
	m_up = glm::vec3(0, 1, 0);
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::lookVertically(float d)
{
	m_pry.x = toolbox::clampFloat(m_pry.x - d, -89.f, 89.f);
}

void PerspectiveCamera::lookHorizontally(float d)
{
	m_pry.z = toolbox::cycleClampFloat(m_pry.z + d, -360, 360);
}

void PerspectiveCamera::zoom(float dist)
{
	m_fov += dist;
}

void PerspectiveCamera::setAspectRatio(float aspect_ratio)
{
	m_aspect_ratio = aspect_ratio;
}

void PerspectiveCamera::setViewRange(float near_plane, float far_plane)
{
	m_near = near_plane;
	m_far = far_plane;
}

void PerspectiveCamera::computeDirectionVectors()
{
	m_view_dir = glm::normalize(glm::vec3(
		cos(glm::radians(m_pry.z)) * cos(glm::radians(m_pry.x)),
		sin(glm::radians(m_pry.x)),
		sin(glm::radians(m_pry.z)) * cos(glm::radians(m_pry.x))
	));
	m_right = glm::normalize(glm::cross(m_view_dir, glm::vec3(0, 1, 0)));
	m_up = glm::normalize(glm::cross(m_right, m_view_dir));
}

glm::mat4 PerspectiveCamera::getViewProjectionTransform()
{
	glm::mat4 projection = glm::perspective(glm::radians(m_fov), m_aspect_ratio, m_near, m_far);
	glm::mat4 view = glm::lookAt(m_pos, m_pos + m_view_dir, m_up);
	return projection * view;
}

glm::vec3 PerspectiveCamera::getViewDirection() const
{
	return m_view_dir;
}

glm::vec3 PerspectiveCamera::getRight() const
{
	return m_right;
}
