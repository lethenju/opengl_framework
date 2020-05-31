/*
MIT License

Copyright (c) 2020 Julien LE THENO

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once
#include "ogl_world.hpp"
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
	Ogl_wrapper(int width, int height, char* name);
	int ogl_glfw_init();
	int setup_window(int width, int height, const char* name);
	int ogl_glew_init();
	int ogl_redraw();
	int ogl_get_mouse_position(float* x, float* y);

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


