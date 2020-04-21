// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "coordinates.hpp"
#include "ogl_wrapper.hpp"
#include "ogl_world.hpp"
#include "geom.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
Ogl_world world = Ogl_world(Color(0.2f,0,0));
static Ogl_wrapper ogl = Ogl_wrapper();

int main(void)
{
	ogl.setup_input_callback((void*)key_callback);
	ogl.ogl_link_world(&world);
	Square s= Square(0,0,50,50, Color(0,1,0));
	world.add_element(s);
	ogl.ogl_calc_vertex_array();
	ogl.ogl_redraw();
	return 0;
}
// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	Element* cube = world.get_element(0);
	if (key == GLFW_KEY_RIGHT) {
		cube->translate(5,0);
	} else if (key == GLFW_KEY_LEFT) {
		cube->translate(-5,0);
	} else if (key == GLFW_KEY_UP) {
		cube->translate(0,-5);
	} else if (key == GLFW_KEY_DOWN) {
		cube->translate(0,5);
	} else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);
	
	ogl.ogl_calc_vertex_array();
}