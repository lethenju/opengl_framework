// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>
#include "coordinates.hpp"
#include "ogl_wrapper.hpp"
#include "ogl_world.hpp"
#include "geom.hpp"
#include "physics.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
Ogl_world world = Ogl_world(Color(0.2f,0,0));
Physics physics_manager;
static Ogl_wrapper ogl = Ogl_wrapper();
static bool continue_flag = true;

int main(void)
{
	ogl.setup_input_callback((void*)key_callback);
	ogl.ogl_link_world(&world);
	world.add_element(Square(0,0,0.2f,0.2f, Color(0,1,0)));
	physics_manager.subscribe(world.get_element(0)); 
	ogl.ogl_calc_vertex_array();

	std::thread physics_thread (my_physics_thread, &physics_manager);
	while (continue_flag) {	
		ogl.ogl_calc_vertex_array();
		ogl.ogl_redraw();
		usleep(500);
	}
	return 0;
}
// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	Element* cube = world.get_element(0);
	std::array<float, 2> v = physics_manager.get_velocity(cube);
	if (key == GLFW_KEY_RIGHT) {
		//cube->translate(0.05f,0);
		physics_manager.set_velocity(cube,v[0]+0.05f, v[1]);
	} else if (key == GLFW_KEY_LEFT) {
//		cube->translate(-0.05f,0);
		physics_manager.set_velocity(cube,v[0]-0.05f, v[1]);
	} else if (key == GLFW_KEY_UP) {
//		cube->translate(0,0.05f);
		physics_manager.set_velocity(cube,v[0], v[1]+0.05f);
	} else if (key == GLFW_KEY_DOWN) {
//		cube->translate(0,-0.05f);
		physics_manager.set_velocity(cube,v[0]+0.1f, v[1]-0.05f);

	} else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    	glfwSetWindowShouldClose(window, GL_TRUE);
		continue_flag = false;
	}
}