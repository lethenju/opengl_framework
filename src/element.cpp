#include "element.hpp"

bool operator==(const Element& e, const Element& e2) {
	return true;
}


// Returns a vector which describe the transformation that the velocity of the object should have.
// Returns [1,1] if no collisions : velocity doesnt change.
std::array<float, 2> Element::translate(float x, float y) {
	std::array<float, 2> collision_force{};
	collision_force[0] = 1;
	collision_force[1] = 1;

	// first: boundary check,
	for (auto& triangle: *this) {
		for (auto& coord : triangle.coordinates){
			// TODO Boundary check 
			// Test a l'arrache
			if (coord.x + x > 0.5 || coord.x + x < -0.5 ){
				collision_force[0] = -1; 
			} 
			if ( coord.y + y > 0.5 || coord.y + y < -0.5 ) {
				collision_force[1] = -1;
			} 
		}
	}
	// then move
	for (auto& triangle: *this) {
		for (auto& coord : triangle.coordinates){
			coord.x += x;
			coord.y += y;
		}
	}
	return collision_force;
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

