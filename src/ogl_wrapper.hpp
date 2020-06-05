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
	 * @param width : width of the window
	 * @param height : height of the window
	 * @param name : title of the window
	 */
	Ogl_wrapper(int width, int height, const char* name);

	/**
	 * Gets the mouse position in the screen
	 * @param x : a pointer to the float that will get updated
	 * @param y : a pointer to the float that will get updated
	 * @return 0 if it worked
	 */
	int ogl_get_mouse_position(float* x, float* y);

	/**
	 * Link a Ogl_world object for getting elements structure and prepare vertex buffers
	 * @param world : a pointer to the Ogl_world instance
	 * @return 0 if it worked
	 */
	int ogl_link_world(Ogl_world* world);
	
	/**
	 * Recomputes the vertex array from the world : each time this function is called
	 * it will get the data in the world and computes vertices and color data that
	 * are understandable by OpenGL
	 * So it needs to be called between adding a shape in your world and calling ogl_redraw
	 */
	int ogl_calc_vertex_array();

	/**
	 * Send the vertex arrays and colors array to opengl, for it to be really displayed on the screen
	 */
	int ogl_redraw();


	/**
	 * Setup an input callback that will be called if there's any type of glfw-sensed input
	 * @param cb : the callback function with the following parameters : GLFWwindow* window, int key, int scancode, int action, int mode
	 */
	int setup_input_callback(void* cb);
private:

	/**
	 * Initialize glfw
	 * @return 0 if it worked
	 */  
	int ogl_glfw_init();

	/**
	 * Setup a window
	 * @param width : width of the window
	 * @param height : height of the window
	 * @param name : title of the window
	 * @return 0 if it worked
	 */  
	int setup_window(int width, int height, const char* name);

	/**
	 * Initialize glew
	 * @return 0 if it worked
	 */  
	int ogl_glew_init();

	// The pointer to the window	
	GLFWwindow* window = nullptr;

	// The pointer to the world
	Ogl_world* world = nullptr;

	// The size of the vertex array
	int vertex_array_size = 0;

	// The vertex array itself
	float* vertex_array = nullptr;
	// The color array (which size is indexed from the vertex array size)
	float* color_array = nullptr;
	
	GLuint vaoID[1];
	GLuint vboID[1];
	GLuint shaderProgram; 
};
