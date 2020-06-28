#include "pch.h"

#include <glad/glad.h>
#include "Window.h"

Window::Window(unsigned int width, unsigned int height, const char* title)
{
	m_size.x = width;
	m_size.y = height;
	init(title);
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::closeButtonPressed()
{
	return glfwWindowShouldClose(m_window);
}

glm::vec2 Window::getSize() const
{
	return m_size;
}

void Window::setSize(unsigned int width, unsigned int height)
{
	glfwSetWindowSize(m_window, width, height);
	m_size.x = width;
	m_size.y = height;
}

void Window::close()
{
	glfwSetWindowShouldClose(m_window, true);
}

void Window::update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

void Window::init(const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(m_size.x, m_size.y, title, NULL, NULL);
	if (m_window == NULL)
	{
		CONSOLE_LOG_ERROR("Window.cpp", "Failed to create glfw window");
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		CONSOLE_LOG_ERROR("Window.cpp", "Failed to initialized opengl");
		glfwTerminate();
	}
}
