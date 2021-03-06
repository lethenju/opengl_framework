/*
MIT License

Copyright (c) 2020 Julien LE THENO

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "ogl_world.hpp"

#include <cstdint>
#include <cstring>
#include <iostream>

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
	if (this->elements.find(id) == this->elements.end()) {
		std::cout << "ERROR : seeking element of ID " << id << " does not exist " << std::endl;
		return nullptr;
	} else {
		return &(this->elements.at(id));
	}
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