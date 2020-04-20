#pragma once
#include "ogl_world.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Ogl_wrapper {
public:
	Ogl_wrapper();
	int ogl_glfw_init();
	int setup_window(int width, int height, const char* name);
	int ogl_glew_init();
	int ogl_redraw();

	// Link a Ogl_world object for getting elements structure and prepare vertex buffers
	int ogl_link_world(Ogl_world* world);
	int ogl_calc_vertex_array();
private:
	
	GLFWwindow* window = nullptr;
	Ogl_world* world = nullptr;
	int vertex_array_size = 900;
	float* vertex_array = nullptr;
	
	GLuint vaoID[1];
	GLuint vboID[1];
	GLuint shaderProgram; 
};


