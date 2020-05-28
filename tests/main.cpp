// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <opengl_framework.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
Ogl_world world = Ogl_world(Color(0.2f,0,0));
Physics physics_manager;
static Ogl_wrapper ogl = Ogl_wrapper(1000, 1000, "Pong");
static bool continue_flag = true;

int main(void)
{
	ogl.setup_input_callback((void*)key_callback);
	ogl.ogl_link_world(&world);
	
	// ball
	world.add_element(Square(0,0,0.2f,0.2f, Color(0,1,0)));
	
	// left pad
	world.add_element(Square(-1,-0.5,0.1f,0.5f, Color(1,1,1)));
	
	// right pad
	world.add_element(Square(1-0.1f,-0.5,0.1f,0.5f, Color(1,1,1)));

	// bottom wall
	world.add_element(Square(-1,-1,2,0.05f, Color(1,1,1)));

	// top wall
	world.add_element(Square(-1,0.95f,2,0.05f, Color(1,1,1)));

	physics_manager.subscribe(world.get_element(0), 0, true); 
	physics_manager.subscribe(world.get_element(1), 0, true); 
	physics_manager.subscribe(world.get_element(2), 0, true); 
	physics_manager.subscribe(world.get_element(3), 0, false);
	physics_manager.subscribe(world.get_element(4), 0, false); 
 
	physics_manager.set_velocity(world.get_element(0),0.05f,0.05f);

	ogl.ogl_calc_vertex_array();
	physics_manager.start();
	while (continue_flag) {	
		Element* Ball_position = world.get_element(0);
		Element* IA_pad        = world.get_element(2);
		float middle_IA_position = IA_pad->get_position().y + IA_pad->get_dimensions()[1]/2;
		float middle_ball_position = Ball_position->get_position().y + Ball_position->get_dimensions()[1]/2;
		IA_pad->translate(0,middle_ball_position-middle_IA_position);
		physics_manager.handle_collisions(&physics_manager.physics_subscribed_elements.at(2), 0,(middle_ball_position-middle_IA_position));
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
	Element* left_pad= world.get_element(1);
	if (key == GLFW_KEY_UP) {
			left_pad->translate(0, 0.1f);
			physics_manager.handle_collisions(&physics_manager.physics_subscribed_elements.at(1), 0, 0.1f);
	} else if (key == GLFW_KEY_DOWN) {
			left_pad->translate(0, -0.1f);
			physics_manager.handle_collisions(&physics_manager.physics_subscribed_elements.at(1), 0, -0.1f);
	} else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    	glfwSetWindowShouldClose(window, GL_TRUE);
		continue_flag = false;
	}
}