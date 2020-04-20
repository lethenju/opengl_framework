
#include <stdio.h>
#include <cstdlib>
#include <cstdio>

#include "shader.hpp"
#include "ogl_wrapper.hpp"

Ogl_wrapper::Ogl_wrapper() {
	this->ogl_glfw_init();
	this->setup_window(1000, 1000, "LOL");
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
	glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
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
	
	this->vertex_array_size = this->world->get_raw_coord_array_size();
	this->vertex_array = new float[this->vertex_array_size];
	this->world->get_raw_coord_array(this->vertex_array);
	
	glGenVertexArrays(1, &(this->vaoID[0]));
	glGenBuffers(1, &(this->vboID[0]));
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(this->vaoID[0]);

	glBindBuffer(GL_ARRAY_BUFFER, this->vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * this->vertex_array_size, this->vertex_array,
	 GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0); 
// Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO 
	//(it's always a good thing to unbind any buffer/array to prevent strange bugs)

	return 0;
}

int Ogl_wrapper::ogl_redraw() {
	while (!glfwWindowShouldClose(this->window))
{
    glfwPollEvents();
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(this->window, GL_TRUE);
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	GLint uniform_id = glGetUniformLocation(shaderProgram, "u_Color");
	 GLfloat color[] = {
        0.0f, 1.0f, 0.0f, 1.0f    };
	glUniform4fv(uniform_id, 1, color);


    //glViewport(0, 0, 1, 1);
	glUseProgram(this->shaderProgram);
    glBindVertexArray(this->vboID[0]);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
}
	return 0;
}

int Ogl_wrapper::ogl_link_world(Ogl_world* world)
{
	this->world = world;
	return 0;
}


