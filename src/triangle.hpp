#pragma once
#include "coordinates.hpp"
#include "color.hpp"
#include <array>

class Triangle
{
public:
	bool is_inside(Coordinates coord);

private:
	Color color;
	std::array<Coordinates, 3> coordinates;

};

