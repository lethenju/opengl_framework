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
// Need to be global for the key callback to access it.
volatile static int left_pad_id;
int main(void)
{
	ogl.setup_input_callback((void*)key_callback);
	ogl.ogl_link_world(&world);
	
	// ball
	int ball_id = world.add_element(Circle(0,0,0.08f, Color(0,1,0)));
	physics_manager.subscribe(world.get_element(ball_id), 0, true); 
	
	// left pad
	left_pad_id = world.add_element(Rectangle(-1,-0.5,0.1f,0.5f, Color(1,1,1)));
	physics_manager.subscribe(world.get_element(left_pad_id), 0, true); 
	
	// right pad
	int right_pad_id =world.add_element(Rectangle(1-0.1f,-0.5,0.1f,0.5f, Color(1,1,1)));
	physics_manager.subscribe(world.get_element(right_pad_id), 0, true); 

	// bottom wall
	int bottom_wall_id = world.add_element(Rectangle(-1,-1,2,0.05f, Color(1,1,1)));
	physics_manager.subscribe(world.get_element(bottom_wall_id), 0, false);

	// top wall
	int top_wall_id = world.add_element(Rectangle(-1,0.95f,2,0.05f, Color(1,1,1)));
	physics_manager.subscribe(world.get_element(top_wall_id), 0, false); 

 
	physics_manager.set_velocity(world.get_element(ball_id),0.05f,0.05f);

	ogl.ogl_calc_vertex_array();
	physics_manager.start();
	while (continue_flag) {	
		Element* Ball_position = world.get_element(ball_id);
		Element* IA_pad        = world.get_element(right_pad_id);
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
	Element* left_pad= world.get_element(left_pad_id);
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