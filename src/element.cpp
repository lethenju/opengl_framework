#include <math.h>
#include "element.hpp"

bool operator==(const Element& e, const Element& e2) {
	return true;
}



int Element::translate(float x, float y) {

	for (auto& triangle: *this) {
		for (auto& coord : triangle.coordinates){
			coord.x += x;
			coord.y += y;
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
}

bool Element::is_colliding_with(Element another_element) {
	for (auto my_triangle : *this) {
		for (auto other_elem_triangle : another_element) {
			for (auto coord : other_elem_triangle.coordinates) {
				// If a coordinate of the another element object is inside my triangle
				if (my_triangle.is_inside(coord)) { 
					return true;
				}
			}
			for (auto coord : my_triangle.coordinates) {
				// If a coordinate of my element object is inside the other element
				if (other_elem_triangle.is_inside(coord)) { 
					return true;
				}
			}
		}
	}
	return false;
}

// Return where my element is compared to the another element
// 0 if up, 1 if right, 2 if down, 3 if left
int Element::get_direction(Element another_element) {

	// I need to count how many of my points are strictly to the top / right / left and bottom of ALL of the points of the other element.
	
	int global_down_score = 0;
	int global_up_score = 0 ;
	int global_right_score = 0 ;
	int global_left_score = 0 ;

	int down_score = 0;
	int up_score = 0 ;
	int right_score = 0 ;
	int left_score = 0 ;
	int maximum = 0;
	// For each of my coordinates
	for (auto my_triangle : *this) {
		for (auto my_coord : my_triangle.coordinates) {
			down_score = 0;
			up_score = 0 ;
			right_score = 0 ;
			left_score = 0 ;
		
			// For each of his coordinates
			for (auto other_elem_triangle : another_element) {
				for (auto other_elem_coord : other_elem_triangle.coordinates) {
					left_score +=  (other_elem_coord.x > my_coord.x);
					right_score +=  (other_elem_coord.x < my_coord.x);
					up_score +=  (other_elem_coord.y > my_coord.y);
					down_score +=  (other_elem_coord.y < my_coord.y);
					
				}
			}

			maximum = std::max(std::max(down_score, up_score),std::max(left_score, right_score));
			global_up_score += (maximum == up_score);
			global_down_score += (maximum == down_score);
			global_right_score += (maximum == right_score); 
			global_left_score += (maximum == left_score) ;
		}
	}

	maximum = std::max(std::max(global_up_score, global_down_score),std::max(global_right_score, global_left_score));
	if (maximum == global_up_score) return 0;
	if (maximum == global_right_score) return 1;
	if (maximum == global_down_score) return 2;
	return 3;
}


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

