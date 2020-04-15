
#include <stdio.h>
#include <cstdlib>
#include <cstdio>


#include "ogl_wrapper.hpp"

Ogl_wrapper::Ogl_wrapper() {
	this->ogl_glfw_init();
	this->setup_window(100, 100, "LOL");
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
	glfwSwapInterval(1);
	return 0;
}

/*
bool Ogl_wrapper::is_not_over()
{
	return (glfwGetKey(this->ogl_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(this->ogl_window) == 0);
}
*/


int Ogl_wrapper::ogl_glew_init() {

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	return 0;
};


int Ogl_wrapper::ogl_redraw() {

	//int programID,unsigned int* our_tab, float *colors
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	/*
	int uniformId = glGetUniformLocation(programID, "u_Color");
	if (uniformId == -1) return -1;
	*/
	
	unsigned int count = 0;
	for (unsigned int y = 0; y < 99; y++) {
		for (unsigned int x = 0; x < 99; x++) {
			/*
			glUniform4f(uniformId, colors[3 * (100 * y + x)     ]
				                 , colors[3 * (100 * y + x) + 1 ]
				                 , colors[3 * (100 * y + x) + 2 ], 0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, our_tab+count);
			count += 6;
			*/
		}
	}

	glDisableVertexAttribArray(0);

	// Swap buffers
	glfwSwapBuffers(this->window);
	glfwPollEvents();
	return 0;
}

int Ogl_wrapper::ogl_link_world(Ogl_world* world)
{
	this->world = world;
	return 0;
}


