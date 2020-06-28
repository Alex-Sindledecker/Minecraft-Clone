#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window
{
public:
	Window(unsigned int width, unsigned int height, const char* title);
	~Window();

	bool closeButtonPressed();
	glm::vec2 getSize() const;
	void setSize(unsigned int width, unsigned int height);
	void close();
	void update();

private:
	void init(const char* title);

	GLFWwindow* m_window;
	glm::vec2 m_size;
};

