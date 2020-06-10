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
static Ogl_wrapper ogl = Ogl_wrapper(1000, 1000, "Platformer");
static bool continue_flag = true;
// Need to be global for the key callback to access it.
volatile static int player_id;
int main(void)
{
	ogl.setup_input_callback((void*)key_callback);
	ogl.ogl_link_world(&world);
	
	// player
	player_id = world.add_element(Rectangle(0,0,0.05f,0.05f, Color(0,1,0)));
	physics_manager.subscribe(world.get_element(player_id), -0.05f, true); 
	
	world.get_element(player_id)->set_stickyness(0.9f);

	// plateform
	int bottom_wall_id = world.add_element(Rectangle(-1,-1,2,0.05f, Color(1,1,1)));
	physics_manager.subscribe(world.get_element(bottom_wall_id), 0, false);

	int platform_1 = world.add_element(Rectangle(-0.2f,-0.8f,0.1f,0.05f, Color(1,1,1)));
	physics_manager.subscribe(world.get_element(platform_1), 0, false);

	int platform_2 = world.add_element(Rectangle(-0.4f,-0.6f,0.1f,0.05f, Color(1,1,1)));
	physics_manager.subscribe(world.get_element(platform_2), 0, false);

	int platform_3 = world.add_element(Rectangle(-0.6f,-0.4f,0.1f,0.05f, Color(1,1,1)));
	physics_manager.subscribe(world.get_element(platform_3), 0, false);


	ogl.ogl_calc_vertex_array();
	physics_manager.start();
	while (continue_flag) {	
        std::cout << "X : " << world.get_element(player_id)->get_position().x << " | Y : " << world.get_element(player_id)->get_position().y << std::endl;
		// Calc vertex and draw calls
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
    
    world.get_element(player_id)->translate(0, 0.001f);
    
	if (key == GLFW_KEY_UP) {
        physics_manager.set_velocity(world.get_element(player_id), 0, 0.1f);
	} else if (key == GLFW_KEY_LEFT) {
        physics_manager.set_velocity(world.get_element(player_id), -0.05f, 0);
    } else if (key == GLFW_KEY_RIGHT) {
        physics_manager.set_velocity(world.get_element(player_id), 0.05f, 0);
	} else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    	glfwSetWindowShouldClose(window, GL_TRUE);
		continue_flag = false;
	}
}