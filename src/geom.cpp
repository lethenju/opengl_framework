#include "element.hpp"
#include "geom.hpp"
#include <cmath>

Rectangle::Rectangle() {
    // Default constructor
}

Rectangle::Rectangle(float x, float y, float width, float height, Color color) {
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

Line::Line(float x1, float y1, float x2, float y2,float thickness, Color color) {
    float x3, y3, x4, y4;

    for (float i = -thickness; i <= thickness; i+=thickness/10) {
        x3 = x1+thickness;
        y3 = y1+thickness;

        x4 = x2+thickness;
        y4 = y2+thickness;
        Tetragon t = Tetragon(x1, y1, x2, y2, x3, y3, x4, y4, color);
        for (auto triangle : t){
            this->push_back(triangle);
        }

    }
}

SevenSegment::SevenSegment(bool segments[7], float x,float y, float width, float  height, Color color) {

    /* h   h
      0**6** w
       4   5
       **3** h/2
       1   2
      0**0** w
       0   0 


    */
   std::array<Rectangle, 7> segments_rect;

    if (segments[0]) {
        segments_rect[0] = Rectangle(x , y, width, 0.01f, color);
    } 
    if (segments[1]) {
        segments_rect[1] = Rectangle(x , y, 0.01f, height/2, color);
    }
    if (segments[2]) {
        segments_rect[2] = Rectangle(x + width - 0.01f, y, 0.01f, height/2, color);
    }
    if (segments[3]) {
        segments_rect[3] = Rectangle(x , y + height/2 - 0.01f, width, 0.01f, color);
    }
    if (segments[4]) {
        segments_rect[4] = Rectangle(x , y + height/2, 0.01f, height/2, color);
    }
    if (segments[5]) {
        segments_rect[5] = Rectangle(x+width-0.01f , y + height/2, 0.01f , height/2, color);
    }
    if (segments[6]) {
        segments_rect[6] = Rectangle(x , y + height - 0.01f, width, 0.01f, color);
    }
    for (auto r : segments_rect) {
        for (auto triangle : r) {
            this->push_back(triangle);
        }
    }
}
