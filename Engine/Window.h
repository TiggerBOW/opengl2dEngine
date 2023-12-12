#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>

using namespace glm;
using namespace std;

class Window
{
public:
	Window();

	Window(GLuint w, GLuint h, string title);
	int Initialize();
	bool getShouldClose();

	int getBufferWidth() { return winBufferWidth; }
	int getBufferHeight() { return winBufferHeight; }

	GLFWwindow* getWindow() { return window; }

	void swapBuffers();
	void clearWindow();
	void clearWindow(vec4 color);

	~Window();

private:
	GLFWwindow* window;
	GLuint winWidth, winHeight;
	GLint winBufferWidth, winBufferHeight;
	string winTitle;
};

