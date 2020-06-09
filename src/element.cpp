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
#include <math.h>
#include <iostream>
#include "element.hpp"
#include "cute_c2.h"



int Element::translate(float x, float y) {

	for (auto& triangle: *this) {
		for (auto& coord : triangle.coordinates){
			coord.x += x;
			coord.y += y;
		}
	}
	return 0;
}

int Element::set_position(float x, float y) {
	Coordinates vec = {0,0};
	bool vec_set = false;
	for (auto& triangle: *this) {
		for (auto& coord : triangle.coordinates){
			if (!vec_set) {
				vec_set = true;
				vec.x = x - coord.x;
				vec.y = y - coord.y;

			}

			coord.x += vec.x;
			coord.y += vec.y;
		}
	}
	return 0;
}
int Element::resize(Coordinates resizePoint, float factorX, float factorY) {
	for (auto& triangle: *this) {
		for (auto& coord : triangle.coordinates){
			float vect_x = coord.x - resizePoint.x;
			float vect_y = coord.y - resizePoint.y;
			vect_x *= factorX;
			vect_y *= factorY;
			coord.x = resizePoint.x + vect_x;
			coord.y = resizePoint.y + vect_y;
		}
	}
	return 0;
}

Coordinates Element::get_center() {
	float x = 0, y = 0, n = 0;
	
	for (auto& triangle: *this) {
		for (auto& coord : triangle.coordinates){
			n++;
			x += coord.x;
			y += coord.y;
		}
	}
	if (n>0) {
		return Coordinates{x/n , y/n};
	}
	return Coordinates{0,0};
}

int Element::rotate(Coordinates rotationPoint, float rad) {
	for (auto& triangle: *this) {
		for (auto& coord : triangle.coordinates){
			// Firstly compute the vector between coord and RotationPoint
			float vect_x = coord.x - rotationPoint.x;
			float vect_y = coord.y - rotationPoint.y;
			// Transfer to polar coordinates
			float r = sqrt(vect_x * vect_x + vect_y * vect_y);
			float theta;
			if (vect_x > 0) {
				 theta = atan(vect_y/vect_x);
			} else if (vect_x < 0) {
				 theta = atan(vect_y/vect_x) + 3.14159f;
			} else if (vect_y > 0){
				 theta =  3.14159f / 2.0f; // Pointing upward
			} else {
				 theta = - 3.14159f / 2.0f; // Pointing downwards
			}
			

			// Apply rotation
			theta += rad;

			// Retransfer to cartesian
			vect_x = r*cos(theta);
			vect_y = r*sin(theta);
			// Recompute the point coords
			coord.x = rotationPoint.x + vect_x;
			coord.y = rotationPoint.y + vect_y;
			
		}
	}
	return 0;
}

bool Element::is_colliding_with(Element another_element) {
	
	c2AABB element_box;
	element_box.min.x = this->get_position().x;
	element_box.min.y = this->get_position().y;
	element_box.max.x = this->get_position().x + this->get_dimensions()[0];
	element_box.max.y = this->get_position().y + this->get_dimensions()[1];


	c2AABB other_element;
	other_element.min.x = another_element.get_position().x;
	other_element.min.y = another_element.get_position().y;
	other_element.max.x = another_element.get_position().x + another_element.get_dimensions()[0];
	other_element.max.y = another_element.get_position().y + another_element.get_dimensions()[1];

	int collide = c2AABBtoAABB(element_box, other_element);
	
	return (collide > 0);
}
/*
// Return where my element is compared to the another element
// 0 if up, 1 if right, 2 if down, 3 if left
int Element::get_direction(Element another_element) {
	
	c2AABB element_box;
	element_box.min.x = this->get_position().x;
	element_box.min.y = this->get_position().y;
	element_box.max.x = this->get_position().x + this->get_dimensions()[0];
	element_box.max.y = this->get_position().y + this->get_dimensions()[1];


	c2AABB other_element;
	other_element.min.x = another_element.get_position().x;
	other_element.min.y = another_element.get_position().y;
	other_element.max.x = another_element.get_position().x + another_element.get_dimensions()[0];
	other_element.max.y = another_element.get_position().y + another_element.get_dimensions()[1];

	c2Manifold m;
	c2AABBtoAABBManifold(element_box, other_element, &m);
	
		std::cout << "m.count = " << m.count << std::endl;

	
		Coordinates contact1 = Coordinates{m.contact_points[0].x,m.contact_points[0].y};
		Coordinates contact2 = Coordinates{m.contact_points[1].x,m.contact_points[1].y};
		std::cout << "contact 1 ( " << contact1.x << " : " << contact1.y << " ) ";
		std::cout << "contact 2 ( " << contact2.x << " : " << contact2.y << " ) " << std::endl;

		
		Coordinates top_left = this->get_position();
		Coordinates top_right = Coordinates{ top_left.x+this->get_dimensions()[0] ,top_left.y};
		Coordinates bottom_left = Coordinates{ top_left.x ,top_left.y-this->get_dimensions()[1]};
		Coordinates bottom_right = Coordinates{  top_right.x , bottom_left.y};
		

		std::cout << "Square to verify top left  ( " << top_left.x << " : " << top_left.y << " ) ";
		std::cout << "Square to verify right bot ( " << bottom_right.x << " : " << bottom_right.y << " ) " << std::endl;

		if  (contact1 == top_left && contact2 == top_right) {
			return 0;
		} else if (contact1 == top_left && contact2 == bottom_left) {
			return 3;
		} else if (contact1 == bottom_left && contact2 == bottom_right) {
			return 2;
		} else {
			return 1;
		}
	
	
}
*/

Coordinates Element::get_position() {
	// we need to get the upper corner coordinates.
	// We take the first available coordinates
	Coordinates best_coord = this->at(0).coordinates.at(0);
	for (auto& triangle: *this) {
		for (auto& coord : triangle.coordinates){
			// if the coordinates are more up-righty than the previous,
			// we swap
			if (coord < best_coord) 
				best_coord = coord;
		}
	}
	return best_coord;
}

std::array<float,2>  Element::get_dimensions() {

	Coordinates position = this->get_position();

	// we need to get the low corner coordinates.
	// We take the first available coordinates
	Coordinates bottom_right = this->at(0).coordinates.at(0);
	for (auto& triangle: *this) {
		for (auto& coord : triangle.coordinates){
			// if the coordinates are more down_lefty than the previous,
			// we swap
			if (coord > bottom_right) 
				bottom_right = coord;
		}
	}
	return bottom_right - position;
}

