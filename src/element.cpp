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

int Element::resize(float factor) {
	// TODO
}

int Element::rotate(float degree) {
	// TODO
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
	int vertical_score = 0;
	int horizontal_score = 0 ;
	// For each of my coordinates
	for (auto my_triangle : *this) {
		for (auto my_coord : my_triangle.coordinates) {
			// For each of his coordinates
			for (auto other_elem_triangle : another_element) {
				for (auto other_elem_coord : other_elem_triangle.coordinates) {
					horizontal_score +=  (other_elem_coord.x > my_coord.x) ? 1 : -1;
					vertical_score +=  (other_elem_coord.y > my_coord.y) ? 1 : -1;
				}
			}
		}
	}
	if (abs(horizontal_score) > abs(vertical_score)) {
		if (horizontal_score > 0) return 1; // right
		return 3; // left
	}
	if (vertical_score > 0) return 0; // up
		return 2; // down 

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

