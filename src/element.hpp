#pragma once
#include <vector>
#include "triangle.hpp"

// Surcharge de std::vector triangles
class Element : public std::vector<Triangle>
{
public:
    int translate(int x, int y);
    int resize(float factor);
    int rotate(float degrees);
};

bool operator==(const Element& e1, const Element& e2);