#include "element.hpp"

bool operator==(const Element& e, const Element& e2) {
	return true;
}


int Element::translate(int x, int y) {
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

std::array<int,2>  Element::get_dimensions() {

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
