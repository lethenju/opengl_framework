/*
MIT License

Copyright (c) 2020 Julien LE THENO

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "element.hpp"

class Rectangle : public Element {
public:
    Rectangle();
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

