#pragma once
#include "Color.h"
#include "ogl_wrapper.hpp"

class Gameworld
{
public:
	int init();
	int init_gameworld();
	int get_pixel(int x, int y, Color* color);
	int set_pixel(int x, int y, Color* color);
	int redraw();
	int cleanup();
	bool is_not_over();
private:
	Ogl_wrapper helper;
	float* g_vertex_buffer_data;
	unsigned int* indices;
	float* colors;

	GLuint vertexbuffer;
	GLuint VertexArrayID;
	GLuint programID;

};

