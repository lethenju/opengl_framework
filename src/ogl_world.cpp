#include "ogl_world.hpp"

#include <cstdint>
#include <cstring>

static int ID_gen = 0;

int Ogl_world::add_element(Element new_element)
{

	ID_gen++;
	this->elements.insert(std::pair<int, Element>(ID_gen, new_element));
	return ID_gen;
}

int Ogl_world::remove_element(int element_ID)
{
	this->elements.erase(element_ID);
	return 0;
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
		for (auto& triangle : std::get<1>(element)){
			if (triangle.is_inside(coord)) {
				return &std::get<1>(element);
			}
		}	
	}
	return nullptr;
}

Element* Ogl_world::get_element(int id)
{
	return &(this->elements.at(id));
}


int Ogl_world::get_raw_coord_array_size() {
	int count = 0;
	for (auto& elem : this->elements) {
		count+= std::get<1>(elem).size() * 3 * 2;
	}
	return count;
}

int Ogl_world::get_raw_coord_array(float* pointer_to_tab) {
	int i = 0;
	for (auto& element : this->elements) {
		for (auto& triangle : std::get<1>(element)) {
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
		for (auto& triangle : std::get<1>(element)) {
			std::memcpy(pointer_to_tab+i  ,&(triangle.color.r), sizeof(float));
			std::memcpy(pointer_to_tab+i+1,&(triangle.color.v), sizeof(float));
			std::memcpy(pointer_to_tab+i+2,&(triangle.color.b), sizeof(float));
			i+=3;	
		}
	} 
	return 0;
}