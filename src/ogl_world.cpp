#include "ogl_world.hpp"



int Ogl_world::add_element(Element new_element)
{

	this->elements.push_back(new_element);
	// Re-compute vertex buffers
	// Launch call for redraw;
	return 0;
}

int Ogl_world::remove_element(Element element_to_remove)
{
	//this->elements.erase(std::remove(this->elements.begin(), this->elements.end(), element_to_remove));
	// Re-compute vertex buffers
	// launch call for redraw
	return 0;
}

int Ogl_world::change_color()
{
	// TODO 
	return 0;
}

Element* Ogl_world::get_element(Coordinates coord)
{
	for (auto& element : this->elements) {
		for (auto& triangle : element) {
			if (triangle.is_inside(coord)) {
				return &element;
			}
		}	
	}

	return nullptr;
}

const std::vector<Element> Ogl_world::get_elements()
{
	return this->elements;
}
