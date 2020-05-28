#include "element.hpp"

class Square : public Element {
public:
    Square(float x, float y, float width, float height, Color color);
};

class Circle : public Element {
public:
    Circle(float x, float y, float radius, Color color);
};
