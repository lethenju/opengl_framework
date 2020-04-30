#include "triangle.hpp"
#include "vector_utils.hpp"


Triangle::Triangle(Coordinates p1, Coordinates p2, Coordinates p3, Color inside_color) {
	this->coordinates = std::array<Coordinates, 3> {p1, p2, p3};
	this->color = inside_color;
}

bool Triangle::is_inside(Coordinates coord)
{
	return (same_side(coord, this->coordinates[0], this->coordinates[1], this->coordinates[2]) &&
			same_side(coord, this->coordinates[1], this->coordinates[0], this->coordinates[2]) &&
			same_side(coord, this->coordinates[2], this->coordinates[0], this->coordinates[1]) );
}
