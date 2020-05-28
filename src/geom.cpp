#include "element.hpp"
#include "geom.hpp"
#include <cmath>

Square::Square(float x, float y, float width, float height, Color color) {
    this->push_back(Triangle(Coordinates{x,y}, Coordinates{x+width, y},  Coordinates{x+width, y+height}, color));
    this->push_back(Triangle(Coordinates{x,y+height}, Coordinates{x, y},  Coordinates{x+width, y+height}, color));
}


Circle::Circle(float x, float y, float radius, Color color) {
    for (float i = 0; i < 2 * 3.1415; i+= 0.01f) {
         this->push_back(
             Triangle(Coordinates{x,y}, 
                      Coordinates{x+radius*std::cos(i), y+ radius*std::sin(i)},  
                      Coordinates{x+radius*std::cos(i+0.01f),y+radius*std::sin(i+0.01f)},
                      color));

    }
}

