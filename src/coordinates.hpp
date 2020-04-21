#pragma once
#include <array>

class Coordinates {
public:
	int x, y;
};

bool operator<(const Coordinates& c1, const Coordinates& c2);
bool operator>(const Coordinates& c1, const Coordinates& c2);

std::array<int, 2> operator-(const Coordinates& c1, const Coordinates& c2);
std::array<int, 2> operator+(const Coordinates& c1, const Coordinates& c2);