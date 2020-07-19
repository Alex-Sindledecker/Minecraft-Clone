#pragma once

class Window;

class Layer
{
public:
	Layer() {}
	virtual ~Layer() = 0 {}

	virtual void onCreate() = 0;
	virtual void onUpdate(float dt) = 0;
	virtual void onRender() = 0;
	void setWindow(Window* window);

protected:
	Window* m_window;
};