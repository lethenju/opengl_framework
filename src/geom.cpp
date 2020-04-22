#include "element.hpp"
#include "geom.hpp"

Square::Square(float x, float y, float width, float height, Color color) {
    this->push_back(Triangle(Coordinates{x,y}, Coordinates{x+width, y},  Coordinates{x+width, y+height}, color));
    this->push_back(Triangle(Coordinates{x,y+height}, Coordinates{x, y},  Coordinates{x+width, y+height}, color));
}
