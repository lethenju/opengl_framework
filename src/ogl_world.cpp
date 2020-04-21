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
	//this->elements.erase(std::remove(this->elements.begin(), this->elements.end(), element_to_remove));

	return 0;
}

int Ogl_world::change_color()
{
	// TODO 
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
	printf("->  %d \n", count);
	return count;
}

int Ogl_world::get_raw_coord_array(float* pointer_to_tab) {
	int i = 0;
	for (auto& element : this->elements) {
		printf("`\nElement :");
		for (auto& triangle : element) {
			printf("`\nTriangle :");
			for (auto& coord : triangle.coordinates) {
				printf("( x : %d y : %d )", coord.x, coord.y);
				float new_x = ((float)coord.x)/100-0.5f;
				float new_y = ((float)coord.y)/100-0.5f;
				
				
				std::memcpy(pointer_to_tab+i  ,&new_x, sizeof(float));
				std::memcpy(pointer_to_tab+i+1,&new_y, sizeof(float));
				i+=2;
			}
		}
	} 
	printf("`\n");

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