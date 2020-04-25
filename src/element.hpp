#pragma once
#include <vector>
#include "triangle.hpp"

// Surcharge de std::vector triangles
class Element : public std::vector<Triangle>
{
public:
    std::array<float, 2> translate(float x, float y);
    int resize(float factor);
    int rotate(float degrees);

    Coordinates get_position();
    std::array<float,2>  get_dimensions();
};

bool operator==(const Element& e1, const Element& e2);