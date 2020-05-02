#pragma once
#include <array>
#include "coordinates.hpp"

// as we're in 2D, the cross product is a scalar : always pointing in the Z direction
float cross_product(std::array<float, 2> v1, std::array<float, 2> v2) {
	return v1[0]*v2[1] - v1[1]*v2[0];
}


bool same_side(Coordinates p1, Coordinates p2, Coordinates A, Coordinates B) {
	std::array<float, 2> vector_A_to_B = {B.x - A.x, B.y - A.y};
	std::array<float, 2> vector_A_to_p1 = {p1.x - A.x, p1.y - A.y};
	std::array<float, 2> vector_A_to_p2 = {p2.x - A.x, p2.y - A.y};

	float cross_prod1 = cross_product(vector_A_to_B, vector_A_to_p1);
	float cross_prod2 = cross_product(vector_A_to_B, vector_A_to_p2);
	return (cross_prod1 * cross_prod2 > 0);
}
