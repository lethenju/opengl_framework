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
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "shader.hpp"
#include "ogl_wrapper.hpp"

Ogl_wrapper::Ogl_wrapper(int width, int height, const char* name) {
	this->ogl_glfw_init();
	this->setup_window(width, height, name);
	this->ogl_glew_init();

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);

	this->world = nullptr;
}

int Ogl_wrapper::ogl_glfw_init() {

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	std::cout << "GLFW Inited correctly" << std::endl;
	return 0;
}

int Ogl_wrapper::setup_window(int width, int height, const char* name)
{

	// Open a window and create its OpenGL context
	this->window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (this->window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(this->window);
	// Set the required callback functions
	glfwSwapInterval(1);

	std::cout << "GLFW window initialised correctly" << std::endl;

	return 0;
}

int Ogl_wrapper::ogl_get_mouse_position(float* x, float* y) {
	double xpos, ypos;
	glfwGetCursorPos( this->window, &xpos, &ypos);
	int width, height;
	glfwGetWindowSize(this->window, &width, &height);
	// Transfer to -1 ; 1 coordinates system
	*x = (float) 2*xpos/width - 1 ;
	*y = (float) - (2*ypos/height - 1 );
	return 0;
}


int Ogl_wrapper::setup_input_callback(void* cb) {
	glfwSetKeyCallback(this->window, (GLFWkeyfun) cb);
	return 0;
}

int Ogl_wrapper::ogl_glew_init() {

	// Initialize GLEW
	glewExperimental = GL_TRUE; // Needed for core profile
	int rv = glewInit();
	if (rv != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW : %d\n", rv);
		getchar();
		glfwTerminate();
		return -1;
	}
	

	this->shaderProgram = LoadShaders("SimpleVertexShader.shader","SimpleFragmentShader.shader");
	return 0;
};

int Ogl_wrapper::ogl_calc_vertex_array() {
	if (this->world == nullptr) 
		return -1;

	if (this->world->get_raw_coord_array_size() == this->vertex_array_size) {
		// Only update data
		this->world->get_raw_coord_array(this->vertex_array);
		this->world->get_raw_color_array(this->color_array);
		glBindVertexArray(this->vaoID[0]);
		glBindBuffer(GL_ARRAY_BUFFER, this->vboID[0]);
	    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GL_FLOAT) * this->vertex_array_size, this->vertex_array);
		glBindBuffer(GL_ARRAY_BUFFER, 0); 
		glBindVertexArray(0); // Unbind VAO 


		return 0;
	} else {

		if (this->color_array != nullptr) {
			delete this->color_array;
		}
		if (this->vertex_array != nullptr) {
			delete this->vertex_array;
		}

		this->vertex_array_size = this->world->get_raw_coord_array_size();
		this->vertex_array = new float[this->vertex_array_size];
		this->world->get_raw_coord_array(this->vertex_array);

		
		glGenVertexArrays(1, &(this->vaoID[0]));
		glGenBuffers(1, &(this->vboID[0]));
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(this->vaoID[0]);

		glBindBuffer(GL_ARRAY_BUFFER, this->vboID[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * this->vertex_array_size, this->vertex_array,
		GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);


		glBindBuffer(GL_ARRAY_BUFFER, 0); 
	// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO 
		//(it's always a good thing to unbind any buffer/array to prevent strange bugs)


		this->color_array = new float[this->vertex_array_size/2]; // from 6 coord float we have 3 color data
		this->world->get_raw_color_array(this->color_array);

	}
	return 0;
}

int Ogl_wrapper::ogl_redraw() {
	
	glfwPollEvents();
	
	Color bg = this->world->get_background();

	glClearColor(bg.r, bg.v, bg.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(this->shaderProgram);

	GLint uniform_id = glGetUniformLocation(shaderProgram, "u_Color");
	glBindVertexArray(this->vaoID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboID[0]);
	// For each triangle
	for (int i =0; i < this->vertex_array_size/(3*2); i++) {
		glUniform4fv(uniform_id, 1, this->color_array+(i*3));
		glDrawArrays(GL_TRIANGLES, i*3, 3);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glfwSwapBuffers(window);

	return 0;
}

int Ogl_wrapper::ogl_link_world(Ogl_world* world)
{
	this->world = world;
	return 0;
}



