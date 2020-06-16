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

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
Ogl_world world = Ogl_world(Color(0, 0, 0));
static Ogl_wrapper ogl = Ogl_wrapper(1000, 1000, "tests geometry");
static bool continue_flag = true;

int main(void)
{
	ogl.setup_input_callback((void *)key_callback);
	ogl.ogl_link_world(&world);


	Text text = Text((const char*)"The quick fox jumps over the lazy dog", -0.8f, 0, 0.025f, 0.05f, 0.005f, Color(1, 1, 1));

    // For each letter in text
    // Todo work on world.add_element with the full text
    for (auto& letter: text){
        // Add the SevenSeg representation in the world
	    world.add_element(*(letter.repr));
    }
	
    Text text2 = Text((const char*)"0123456789 - testing opengl framework", -0.8f, 0.1f, 0.025f, 0.05f, 0.005f, Color(0.5f, 0.8f, 0.2f));

    for (auto& letter: text2){
	    world.add_element(*(letter.repr));
    }
	
	while (continue_flag)
	{
		ogl.ogl_calc_vertex_array();
		ogl.ogl_redraw();
		usleep(500);
	}
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		continue_flag = false;
	}
}