// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <opengl_framework.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
Ogl_world world = Ogl_world(Color(0,0,0));
Physics physics_manager;
static Ogl_wrapper ogl = Ogl_wrapper(1000, 1000, "tests collision");
static bool continue_flag = true;
volatile static int square_id;

int main(void)
{
    ogl.setup_input_callback((void*)key_callback);
	ogl.ogl_link_world(&world);
	for (float a = -0.70f ; a < 0.80f; a += 0.1f) {
		for (float b = -0.70f ; b < 0.80f; b += 0.1f) {
			world.add_element(Rectangle(0.01f+a,0.01f+b,0.08f,0.08f, Color(0.1f,0.1f,0.1f)));
		}
	}
	// First element
	square_id = world.add_element(Rectangle(0.01f,0.01f,0.08f,0.08f, Color(1,1,1)));
	
	// walls
	int wall_1_id = world.add_element(Rectangle(0.8f,-0.8f,0.1f,1.6f, Color(0.5f,0.5f,0.5f)));
	int wall_2_id = world.add_element(Rectangle(-0.8f,-0.8f,1.6f,0.1f, Color(0.5f,0.5f,0.5f)));
	int wall_3_id = world.add_element(Rectangle(-0.8f,-0.8f,0.1f,1.6f, Color(0.5f,0.5f,0.5f)));
	int wall_4_id = world.add_element(Rectangle(-0.8f,0.8f,1.7f,0.1f, Color(0.5f,0.5f,0.5f)));



	
	physics_manager.subscribe(world.get_element(square_id), 0, true); 
	physics_manager.subscribe(world.get_element(wall_1_id), 0, false); 
	physics_manager.subscribe(world.get_element(wall_2_id), 0, false); 
	physics_manager.subscribe(world.get_element(wall_3_id), 0, false); 
	physics_manager.subscribe(world.get_element(wall_4_id), 0, false); 

	ogl.ogl_calc_vertex_array();
	physics_manager.start();
	while (continue_flag) {	
		ogl.ogl_calc_vertex_array();
		ogl.ogl_redraw();
		usleep(500);
	}
	physics_manager.stop();
	return 0;
}



// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	Element* user= world.get_element(square_id);
	if (key == GLFW_KEY_UP  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
			user->translate(0, 0.1f);
			physics_manager.handle_collisions(&physics_manager.physics_subscribed_elements.at(0), 0, 0.1f);
	} else if (key == GLFW_KEY_DOWN  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
			user->translate(0, -0.1f);
			physics_manager.handle_collisions(&physics_manager.physics_subscribed_elements.at(0), 0, -0.1f);
	} else if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
			user->translate(0.1f, 0);
			physics_manager.handle_collisions(&physics_manager.physics_subscribed_elements.at(0), 0.1f, 0);
	} else if (key == GLFW_KEY_LEFT  && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
			user->translate(-0.1f, 0);
			physics_manager.handle_collisions(&physics_manager.physics_subscribed_elements.at(0), -0.1f, 0);
				
	} else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    	glfwSetWindowShouldClose(window, GL_TRUE);
		continue_flag = false;
	}
}