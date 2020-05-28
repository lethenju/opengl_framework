#include "element.hpp"

class Square : public Element {
public:
    Square(float x, float y, float width, float height, Color color);
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

