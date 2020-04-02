#include "Gameworld.h"
#include "ogl_wrapper.hpp"
#include "shader.hpp"

int Gameworld::init()
{

	this->helper = Ogl_wrapper();
	this->helper.Ogl_glfw_init();
	this->helper.Ogl_window(1000, 1000, "My window");
	this->helper.Ogl_glew_init();

	return 0;
}

int Gameworld::init_gameworld()

{
	this->g_vertex_buffer_data = new float[40 * 40 * 2]();

	unsigned int count = 0;
	for (int i = -100; i < 100; i += 5) {
		for (int j = -100; j < 100; j += 5) {
			this->g_vertex_buffer_data[count] = (float)i / 100;
			this->g_vertex_buffer_data[count + 1] = (float)j / 100;
			count += 2;
		}
	}


	this->indices = new unsigned int[40 * 40 * 6]();
	count = 0;
	for (unsigned int i = 0; i < 39 * 39; i++) {
		if ((i + 1) % 40 == 0) i++;
		this->indices[count] = i;
		this->indices[count + 1] = i + 1;
		this->indices[count + 2] = i + 40;
		this->indices[count + 3] = this->indices[count + 1];
		this->indices[count + 4] = this->indices[count + 2];
		this->indices[count + 5] = this->indices[count + 2] + 1;
		count += 6;
	}


	this->colors = new float[40 * 40 * 3]();


	// Create and compile our GLSL program from the shaders
	this->programID = LoadShaders("SimpleVertexShader.shader", "SimpleFragmentShader.shader");

	glGenVertexArrays(1, &this->VertexArrayID);
	glBindVertexArray(this->VertexArrayID);


	glGenBuffers(1, &this->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 40 * 40 * 2, this->g_vertex_buffer_data, GL_STATIC_DRAW);
	glUseProgram(this->programID);
	return 0;
}

int Gameworld::get_pixel(int x, int y, Color* color)
{
	return 0;
}

int Gameworld::set_pixel(int x, int y, Color* color)
{
	this->colors[3 * (39 * y + x)] = color->r;
	this->colors[3 * (39 * y + x) + 1 ] = color->v;
	this->colors[3 * (39 * y + x) + 2 ] = color->b;
	


	return 0;
}

int Gameworld::redraw() {
	this->helper.Ogl_redraw(this->programID, this->indices, this->colors);
	return 0;
}

int Gameworld::cleanup()
{
	
	// Cleanup VBO
	glDeleteBuffers(1, &this->vertexbuffer);
	glDeleteVertexArrays(1, &this->VertexArrayID);
	glDeleteProgram(this->programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

bool Gameworld::is_not_over()
{
	// TODO real input management
	return this->helper.is_not_over();
}
