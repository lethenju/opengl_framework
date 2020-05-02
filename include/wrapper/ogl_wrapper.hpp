#pragma once
#include "../world/ogl_world.hpp"
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
/**
 * Represent OpenGL, act as a layer to put everything directly related to opengl, glfw and glew inside
 */ 
class Ogl_wrapper {
public:
	/**
	 * Constructor of Ogl_wrapper
	 */
	Ogl_wrapper();
	int ogl_glfw_init();
	int setup_window(int width, int height, const char* name);
	int ogl_glew_init();
	int ogl_redraw();

	// Link a Ogl_world object for getting elements structure and prepare vertex buffers
	int ogl_link_world(Ogl_world* world);
	int ogl_calc_vertex_array();
	int setup_input_callback(void* cb);
private:
	
	GLFWwindow* window = nullptr;
	Ogl_world* world = nullptr;
	int vertex_array_size = 0;
	float* vertex_array = nullptr;
	float* color_array = nullptr;
	
	GLuint vaoID[1];
	GLuint vboID[1];
	GLuint shaderProgram; 
};


