#include "element.hpp"

class Rectangle : public Element {
public:
    Rectangle(float x, float y, float width, float height, Color color);
};

class Circle : public Element {
public:
    Circle(float x, float y, float radius, Color color);
};


class Tetragon : public Element {
public:
    Tetragon(float x1, float y1, float x2, float y2, 
             float x3, float y3, float x4, float y4, Color color);
};


class Line : public Element {
public:
    Line(float x1, float y1, float x2, float y2, float thickness, Color color);
};

class SevenSegment : public Element {
public:
    //  |=b6=|
    // b4    b5
    //  * b3 *
    // b1    b2
    //  |=0=|
    SevenSegment(bool segments[7], float x, float y,float width,float height, Color color);
};

