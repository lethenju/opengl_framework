#include "coordinates.hpp"

bool operator<(const Coordinates& c1, const Coordinates& c2) {
    return (c1.x + c1.y) < (c2.x + c2.y);
}

bool operator>(const Coordinates& c1, const Coordinates& c2) {
    return (c1.x + c1.y) > (c2.x + c2.y);
}

std::array<float, 2> operator-(const Coordinates& c1, const Coordinates& c2) {
    std::array<float, 2> values;
    values[0] = c1.x - c2.x;
    values[1] = c1.y - c2.y;
    return values;
}
std::array<float, 2> operator+(const Coordinates& c1, const Coordinates& c2) {
    std::array<float, 2> values;
    values[0] = c1.x + c2.x;
    values[1] = c1.y + c2.y;
    return values;
}