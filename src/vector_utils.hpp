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
