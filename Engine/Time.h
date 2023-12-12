#pragma once

#include <GLFW/glfw3.h>


class Time
{
public:
	Time();
	void setFps(float fps);

	static float deltaTime;
private:
	double lastTime;
	double targetFrameTime;
};

