#pragma once
#include <vector>
#include "triangle.hpp"

// Surcharge de std::vector triangles
class Element : public std::vector<Triangle>
{


};

bool operator==(const Element& e1, const Element& e2);