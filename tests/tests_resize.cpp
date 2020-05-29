// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
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

	// circle
	int circle_id = world.add_element(Circle(0.5f,0,0.2f, Color(0,1,1)));
	
	// tetragon
	int tetragon_id = world.add_element(Tetragon(-0.7f,-0.2f,
                               -0.4f,-0.02f,
                               -0.3f, 0.3f,
                               -0.8f, 0.1f, Color(1,1,0)));

	// line
	int line_id = world.add_element(Line(-0.9f,-0.8f,
						   -0.4f,-0.7f, 0.005f, Color(0.8f,1,0.2f)));
	
	

	float osc = 0;
	while (continue_flag) {
		osc+=0.05f;
		float sizing = 1 + cos(osc)/50;
		Coordinates center_square =  world.get_element(square_id)->get_center();
		world.get_element(square_id)->resize(center_square, sizing,sizing);
		
		Coordinates center_line = world.get_element(line_id)->get_center();
		world.get_element(line_id)->resize(center_square, sizing, 1);

		// Rotate around the square
		world.get_element(tetragon_id)->resize(center_square, sizing,1);
		world.get_element(circle_id)->resize(center_square, 1,sizing);

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