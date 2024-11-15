#include "Time.h"
#include <GLFW/glfw3.h>

namespace Time {
	double lastFrame = 0.0;
	double thisFrame = lastFrame;
	double deltaTimeAccumulator = 0.0;
	double deltaTime = lastFrame - thisFrame;
}

void Time::Init() {
	lastFrame = glfwGetTime();
	thisFrame = lastFrame;
	deltaTimeAccumulator = 0.0;
	deltaTime = lastFrame - thisFrame;
}

void Time::Update() {
	lastFrame = thisFrame;
	thisFrame = glfwGetTime();
	deltaTime = thisFrame - lastFrame;
	deltaTimeAccumulator += deltaTime;
}