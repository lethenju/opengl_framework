#pragma once
#include "coordinates.hpp"
#include "color.hpp"
#include <array>

class Triangle
{
public:
	Triangle(Coordinates p1, Coordinates p2, Coordinates p3, Color inside_color);
	bool is_inside(Coordinates coord);

	Color color;
	std::array<Coordinates, 3> coordinates;

};

