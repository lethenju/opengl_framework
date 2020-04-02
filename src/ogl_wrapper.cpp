
#include <stdio.h>
#include <cstdlib>
#include <cstdio>


#include "ogl_wrapper.hpp"

int Ogl_wrapper::Ogl_glfw_init() {

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return 0;
}


int Ogl_wrapper::Ogl_window(int width, int height, const char* name) {

	// Open a window and create its OpenGL context
	this->ogl_window = glfwCreateWindow(width, height, name, NULL, NULL);
	if (ogl_window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
	}
	glfwMakeContextCurrent(this->ogl_window);
	glfwSwapInterval(1);

	return 0;
}
bool Ogl_wrapper::is_not_over()
{
	return (glfwGetKey(this->ogl_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(this->ogl_window) == 0);
}


int Ogl_wrapper::Ogl_glew_init() {

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(this->ogl_window, GLFW_STICKY_KEYS, GL_TRUE);
	return 0;
};

int Ogl_wrapper::Ogl_redraw(int programID,unsigned int* our_tab, float *colors) {

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


	int uniformId = glGetUniformLocation(programID, "u_Color");
	if (uniformId == -1) return -1;

	
	unsigned int count = 0;
	for (unsigned int y = 0; y < 40; y++) {
		for (unsigned int x = 0; x < 40; x++) {

			glUniform4f(uniformId, colors[3*(40*y+x)], colors[3 * (40* y + x)+1], colors[3 * (40 * y + x)+2], 0);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, our_tab+count);
			count += 6;
		}
	}

	glDisableVertexAttribArray(0);

	// Swap buffers
	glfwSwapBuffers(ogl_window);
	glfwPollEvents();
	return 0;
}
