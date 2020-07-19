#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window
{
public:
	Window() {}
	Window(unsigned int width, unsigned int height, const char* title, bool fullscreen = false);
	~Window();

	void create(unsigned int width, unsigned int height, const char* title, bool fullscreen = false);
	bool closeButtonPressed();
	bool isKeyPressed(int key);
	glm::vec2 getSize() const;
	glm::vec2 getMousePos() const;
	void setMousePos(float x, float y);
	void setMousePos(glm::vec2 pos);
	void setSize(unsigned int width, unsigned int height);
	void setTitle(const char* title);
	void close();
	void update();

private:
	void init(const char* title, bool fullscreen);

	GLFWwindow* m_window;
	glm::vec2 m_size;
};

