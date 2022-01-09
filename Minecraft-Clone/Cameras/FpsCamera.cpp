#include "FpsCamera.h"

#include "../Application/Application.h"

#include <iostream>

void FpsCamera::update(float dt)
{
	GLFWwindow* window = Application::get().getWindow();
	float winWidth = Application::get().getWindowWidth();
	float winHeight = Application::get().getWindowHeight();

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glfwSetCursorPos(window, winWidth / 2.f, winHeight / 2.f);

	float xoffset = winWidth / 2.f - xpos;
	float yoffset = winHeight / 2.f - ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw -= xoffset;
	pitch += yoffset;

	const float thresh = 89.f;
	if (pitch > thresh)
		pitch = thresh;
	if (pitch < -thresh)
		pitch = -thresh;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(direction);

	const float cameraSpeed = 5 * dt; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		pos += cameraSpeed * front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		pos -= cameraSpeed * front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		pos -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		pos += glm::normalize(glm::cross(front, up)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void FpsCamera::updateProjection()
{
	projection = glm::perspective(glm::radians(45.f), Application::get().getAspectRatio(), 0.1f, 100.f);
}

void FpsCamera::updateView()
{
	view = glm::lookAt(pos, pos + front, up);
	//view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

glm::mat4 FpsCamera::getViewProjection()
{
	return projection * view;
}
