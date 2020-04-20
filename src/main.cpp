// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "coordinates.hpp"
#include "ogl_wrapper.hpp"
#include "ogl_world.hpp"
#include "geom.hpp"


int main(void)
{
	Ogl_wrapper ogl = Ogl_wrapper();
	Ogl_world world = Ogl_world(Color(0.2f,0,0));
	ogl.ogl_link_world(&world);
	Element e;
	e.push_back(Triangle(Coordinates{ 0, 0 }, Coordinates{ 100, 0 }, Coordinates{ 100, 100 }, Color(1,0,1)));
	e.push_back(Triangle(Coordinates{ -40, 0 }, Coordinates{ -50, 50 }, Coordinates{ 0, 0 }, Color(1,1,1)));
	Square s= Square(0,0,200,40, Color(1,0,0));
	world.add_element(s);
	world.add_element(e);
	ogl.ogl_calc_vertex_array();
	ogl.ogl_redraw();
	return 0;
}
