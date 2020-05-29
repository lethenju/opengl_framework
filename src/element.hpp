#pragma once
#include <vector>
#include <stdlib.h>
#include "triangle.hpp"

// Element class, overloading std::vector.
class Element : public std::vector<Triangle>
{
public:
    int translate(float x, float y);
    int resize(float factor);
    int rotate(Coordinates rotationPoint, float rad);
    Coordinates get_center();
    Coordinates get_position();
    std::array<float,2>  get_dimensions();
    bool is_colliding_with(Element another_element);
    int get_direction(Element another_element);

};

bool operator==(const Element& e1, const Element& e2);