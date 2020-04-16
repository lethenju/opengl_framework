
#include <stdio.h>
#include <cstdlib>
#include <cstdio>

#include "shader.hpp"
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

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);

	GLuint shaderProgram = LoadShaders("SimpleVertexShader.shader","SimpleFragmentShader.shader");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	this->uniform_id = glGetUniformLocation(shaderProgram, "u_Color");


	glGenVertexArrays(1, &(this->vao));
	glBindVertexArray(this->vao);

	glGenBuffers(1, &(this->vbo)); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertex_array_size, 
	         	this->vertex_array, GL_STREAM_DRAW );
	return 0;
};

int Ogl_wrapper::ogl_calc_vertex_array() {
	if (this->world == nullptr) 
		return -1;
	
	this->vertex_array_size = this->world->get_raw_coord_array_size();
	this->vertex_array = new float[this->vertex_array_size];
	this->world->get_raw_coord_array(this->vertex_array);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertex_array_size, 
	         	this->vertex_array, GL_STREAM_DRAW );
	
}

int Ogl_wrapper::ogl_redraw() {
	for (int i = 0; i <this->vertex_array_size; i+=2) {
		printf("%f %f\n", *(this->vertex_array+i), *(this->vertex_array+i+1));
	}
		//int programID,unsigned int* our_tab, float *colors
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);



	glUniform3f(this->uniform_id, 1.0f, 0.0f, 0.0f);

	glDrawArrays(GL_TRIANGLES, 0, this->vertex_array_size/2);


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


