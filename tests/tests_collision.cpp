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
Ogl_world world = Ogl_world(Color(0,0,0));
Physics physics_manager;
static Ogl_wrapper ogl = Ogl_wrapper(1000,1000, "tests collisions");
static bool continue_flag = true;

int main(void)
{
    ogl.setup_input_callback((void*)key_callback);
	ogl.ogl_link_world(&world);
	
	// First element
	int first_id = world.add_element(Rectangle(-1.0f,0,0.2f,0.2f, Color(0,1,0)));
	
	// wall
	int wall_id = world.add_element(Rectangle(0.8f,-1.0f,0.1f,2.0f, Color(1,1,1)));
	
	physics_manager.subscribe(world.get_element(first_id), 0, true); 
	physics_manager.subscribe(world.get_element(wall_id), 0, false); 
    float velocity = 0.1f;
	physics_manager.set_velocity(world.get_element(first_id), velocity,0);

	ogl.ogl_calc_vertex_array();
	physics_manager.start();
	while (continue_flag) {	
		Element* first_element = world.get_element(first_id);
		Element* wall          = world.get_element(wall_id);
		physics_manager.handle_collisions(&physics_manager.physics_subscribed_elements.at(0), physics_manager.get_velocity(first_element)[0], 0);


        if (first_element->get_position().x > wall->get_position().x) {
            // Collision failed.
            std::cout << "Collision failed !" << std::endl;
            std::cout << "Position of ball : x=" << first_element->get_position().x;
            std::cout << "  y="<< first_element->get_position().y << std::endl;

            std::cout << "Position of wall : x=" << wall->get_position().x;
            std::cout << "  y="<< wall->get_position().y << std::endl;
            return -1;

        }

        if (physics_manager.get_velocity(first_element)[0] < 0.0f && first_element->get_position().x < -0.5f) {
            // Success
            // The ball bounced and now its going the other way
            std::cout << "Collision Success ! Try again with more velocity" << std::endl;
            std::cout << "Velocity = " << velocity << std::endl;
            
            velocity+=0.01f;
            physics_manager.set_velocity(first_element, velocity, 0);
        }
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
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    	glfwSetWindowShouldClose(window, GL_TRUE);
		continue_flag = false;
	}
}