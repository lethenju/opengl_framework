#pragma once
#include <vector>
#include "triangle.hpp"

// Element class, overloading std::vector.
class Element : public std::vector<Triangle>
{
public:
    int translate(float x, float y);
    int resize(float factor);
    int rotate(float degrees);

    Coordinates get_position();
    std::array<float,2>  get_dimensions();
};

bool operator==(const Element& e1, const Element& e2);