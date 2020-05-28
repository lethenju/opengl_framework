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


Tetragon::Tetragon(float x1, float y1, float x2, float y2, 
                   float x3, float y3, float x4, float y4, Color color) {
    this->push_back(Triangle(Coordinates{x1,y1}, Coordinates{x2, y2},  Coordinates{x3, y3}, color));
    this->push_back(Triangle(Coordinates{x2,y2}, Coordinates{x1, y1},  Coordinates{x4, y4}, color));
    this->push_back(Triangle(Coordinates{x1,y1}, Coordinates{x4, y4},  Coordinates{x3, y3}, color));
    this->push_back(Triangle(Coordinates{x2,y2}, Coordinates{x4, y4},  Coordinates{x3, y3}, color));
}
