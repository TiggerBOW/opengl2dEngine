#pragma once

#include <GLFW/glfw3.h>

class Input
{
public:
	static bool keyPressing(int key,GLFWwindow *window);
	static bool keyPressed(int key, GLFWwindow* window);
	static bool keyPressUp(int key,GLFWwindow* window);
};

