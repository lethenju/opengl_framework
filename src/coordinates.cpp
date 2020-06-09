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
#include "coordinates.hpp"

bool operator==(const Coordinates& c1, const Coordinates& c2) {
    return (c1.x == c2.x) && (c1.y == c2.y);
}

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