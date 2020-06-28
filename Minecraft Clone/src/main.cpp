#include "pch.h"
#include "Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
	CONSOLE_LOG_ERROR("main.cpp", "This is a test error msg");
	CONSOLE_LOG_WARNING("main.cpp", "This is a test warning msg");
	FILE_LOG_ERROR("main.cpp", "This is a test error msg");
	FILE_LOG_WARNING("main.cpp", "This is a test warning msg");
	return 0;
}