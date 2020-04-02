#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Include GLEW

class Ogl_wrapper {
public:
	int Ogl_glfw_init();
	int Ogl_redraw(int programID, unsigned int* indices, float *colors);
	int Ogl_glew_init();
	int Ogl_window(int width, int height, const char* name);
	bool is_not_over();
private:
	GLFWwindow* ogl_window;
};


