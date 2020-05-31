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
	bool a[7] = {0, 1, 1, 1, 1, 1, 1};
	bool b[7] = {1, 1, 1, 1, 1, 0, 0};
	bool c[7] = {1, 1, 0, 1, 0, 0, 0};
	bool d[7] = {1, 1, 1, 1, 0, 1, 0};
	bool e[7] = {1, 1, 0, 1, 1, 0, 1};
	bool f[7] = {0, 1, 0, 1, 1, 0, 1};
    // seven seg
	int a_id = world.add_element(SevenSegment(a, 0,0,0.1f,0.2f, Color(1,0,0)));
	int b_id = world.add_element(SevenSegment(b, 0.12f,0,0.1f,0.2f, Color(0,1,1)));
	int c_id = world.add_element(SevenSegment(c, 0.24f,0,0.1f,0.2f, Color(0.8f,1,0.5f)));
	int d_id = world.add_element(SevenSegment(d, 0.36f,0,0.1f,0.2f, Color(0.7f,0.5f,1)));
	int e_id = world.add_element(SevenSegment(e, 0.48f,0,0.1f,0.2f, Color(0.5f,0.5f,1)));
	int f_id = world.add_element(SevenSegment(f, 0.60f,0,0.1f,0.2f, Color(0,1,0.5f)));

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
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    	glfwSetWindowShouldClose(window, GL_TRUE);
		continue_flag = false;
	}
}