// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "coordinates.hpp"
#include "ogl_wrapper.hpp"
#include "ogl_world.hpp"



int main(void)
{
	Ogl_wrapper ogl = Ogl_wrapper();
	Ogl_world world = Ogl_world();
	ogl.ogl_link_world(&world);
	Element e;
	e.push_back(Triangle(Coordinates{ 0, 0 }, Coordinates{ 50, 0 }, Coordinates{ 0, 50 }, Color(1,1,1)));
	world.add_element(e);
	ogl.ogl_calc_vertex_array();
	while (1) {
		ogl.ogl_redraw();
	}
	return 0;
}
