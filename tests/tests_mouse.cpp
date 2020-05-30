// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <opengl_framework.hpp>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
Ogl_world world = Ogl_world(Color(0,0,0));
static Ogl_wrapper ogl = Ogl_wrapper(1000,1000, "tests geometry");
static bool continue_flag = true;

int main(void)
{
    ogl.setup_input_callback((void*)key_callback);
	ogl.ogl_link_world(&world);

    // square
	int square_id = world.add_element(Rectangle(0,0,0.2f,0.2f, Color(0,1,0)));
	

    float xpos, ypos;

	while (continue_flag) {
        
		auto cursor = world.get_element(square_id);
        // Get mouse position
        ogl.ogl_get_mouse_position(&xpos, &ypos);
        cursor->set_position(xpos, ypos);

		cursor->rotate(cursor->get_center(), 0.02f);
		
		ogl.ogl_calc_vertex_array();
		ogl.ogl_redraw();
		usleep(500);
	}
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