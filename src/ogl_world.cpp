#include "ogl_world.hpp"

#include <cstdint>
#include <cstring>

int Ogl_world::add_element(Element new_element)
{

	this->elements.push_back(new_element);
	return 0;
}

int Ogl_world::remove_element(Element element_to_remove)
{
	for (int count = 0; count < this->elements.size(); count++) {
		if (this->elements.at(count) == element_to_remove) {
			this->elements.erase(this->elements.begin()+count);
			return 0;
		}
	}
	return -1; // element not found
}

int Ogl_world::set_background(Color new_background) {
	this->bg = new_background;
	return 0;
}

Color Ogl_world::get_background() {
	return this->bg;
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

Element* Ogl_world::get_element(int nb)
{
	return &(this->elements.at(nb));
}

const std::vector<Element> Ogl_world::get_elements()
{
	return this->elements;
}
int Ogl_world::get_raw_coord_array_size() {
	int count = 0;
	for (auto& elem : this->elements) {
		count+= elem.size() * 3 * 2;
	}
	return count;
}

int Ogl_world::get_raw_coord_array(float* pointer_to_tab) {
	int i = 0;
	for (auto& element : this->elements) {
		for (auto& triangle : element) {
			for (auto& coord : triangle.coordinates) {

				std::memcpy(pointer_to_tab+i  , &(coord.x), sizeof(float));
				std::memcpy(pointer_to_tab+i+1, &(coord.y), sizeof(float));
				i+=2;
			}
		}
	} 

	return 0;
}
int Ogl_world::get_raw_color_array(float* pointer_to_tab) {
	int i = 0;
	for (auto& element : this->elements) {
		for (auto& triangle : element) {
			std::memcpy(pointer_to_tab+i  ,&(triangle.color.r), sizeof(float));
			std::memcpy(pointer_to_tab+i+1,&(triangle.color.v), sizeof(float));
			std::memcpy(pointer_to_tab+i+2,&(triangle.color.b), sizeof(float));
			i+=3;	
		}
	} 
	return 0;
}