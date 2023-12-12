#include "Window.h"
#include <iostream>
Window::Window() {
	winWidth = 800;
	winHeight = 600;
}
Window::Window(GLuint w, GLuint h, string title) {
	winWidth = w;
	winHeight = h;
	winTitle = title;
}
int Window::Initialize() {

	//GLFW ba�lat�l�r...
	if (!glfwInit()) {
		printf("GLFW ba�lat�lamad�");
		glfwTerminate();
		return 1;
	}

	window = glfwCreateWindow(winWidth,winHeight,winTitle.c_str(), NULL, NULL);
	if (!window) {
		printf("Pencere olu�turulamad�");
		glfwTerminate();
		return 1;
	}

	//Pencere �zellikleri
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Core profili
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Buffer boyutlar� al�nd�
	glfwGetFramebufferSize(window,&winBufferWidth,&winBufferHeight);
	//GLEW i�in i�erik kurulumu
	glfwMakeContextCurrent(window);

	//Modern eklenti yeniliklerine izin vermek
	glewExperimental = GL_TRUE;

	//Glew ba�lat�lmas�
	if (glewInit() != GLEW_OK) {
		printf("GLEW Ba�lat�lmas� ba�ar�s�z oldu !");
		glfwDestroyWindow(window);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0,0,winBufferWidth,winBufferHeight);
}
void Window::swapBuffers() {
	glfwSwapBuffers(window);
}
void Window::clearWindow() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::clearWindow(vec4 color) {
	//Pencereyi temizle
	glClearColor(color.x,color.y,color.z,color.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
bool Window::getShouldClose() {
	return glfwWindowShouldClose(window);
}
Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}
