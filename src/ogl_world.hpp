#pragma once
#include "coordinates.hpp"
#include "element.hpp"
class Ogl_world
{
public:
	int add_element(Element new_element);
	int remove_element(Element element_to_remove);
	int change_color();
	Element* get_element(Coordinates coord);

	// Return an ro version of the element list (to prevent modification from outside the class.. We can expose our world but not expose the ways to modify it
	const std::vector<Element> get_elements();

	int get_raw_coord_array_size();
	int get_raw_coord_array(float* pointer_to_tab);
	

private:
	std::vector<Element> elements;
};


