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

