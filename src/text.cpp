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
#include "text.hpp"

Letter::Letter(char c, float x, float y, float width, float height, Color color)
{
    c = std::toupper(c);
    switch (c)
    {
    case 'A':
    {
        bool sevenSegArray[7] = {0, 1, 1, 1, 1, 1, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'B':
    {
        bool sevenSegArray[7] = {1, 1, 1, 1, 1, 0, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'C':
    {
        bool sevenSegArray[7] = {1, 1, 0, 1, 0, 0, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'D':
    {
        bool sevenSegArray[7] = {1, 1, 1, 1, 0, 1, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'E':
    {
        bool sevenSegArray[7] = {1, 1, 0, 1, 1, 0, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'F':
    {
        bool sevenSegArray[7] = {0, 1, 0, 1, 1, 0, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'G':
    {
        bool sevenSegArray[7] = {1, 1, 1, 0, 1, 0, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'H':
    {
        bool sevenSegArray[7] = {0, 1, 1, 1, 1, 0, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'I':
    {
        bool sevenSegArray[7] = {0, 0, 1, 0, 0, 0, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'J':
    {
        bool sevenSegArray[7] = {1, 1, 1, 0, 0, 1, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'K':
    {
        bool sevenSegArray[7] = {0, 1, 1, 1, 1, 0, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'L':
    {
        bool sevenSegArray[7] = {1, 1, 0, 0, 1, 0, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'M':
    {
        bool sevenSegArray[7] = {0, 1, 1, 1, 0, 0, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'N':
    {
        bool sevenSegArray[7] = {0, 1, 1, 1, 0, 0, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'O':
    {
        bool sevenSegArray[7] = {1, 1, 1, 1, 0, 0, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'P':
    {
        bool sevenSegArray[7] = {0, 1, 0, 1, 1, 1, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'Q':
    {
        bool sevenSegArray[7] = {0, 0, 1, 1, 1, 1, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'R':
    {
        bool sevenSegArray[7] = {0, 1, 0, 1, 0, 0, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'S':
    {
        bool sevenSegArray[7] = {1, 0, 1, 1, 1, 0, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'T':
    {
        bool sevenSegArray[7] = {1, 1, 0, 1, 1, 0, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'U':
    {
        bool sevenSegArray[7] = {1, 1, 1, 0, 1, 1, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'V':
    {
        bool sevenSegArray[7] = {1, 1, 1, 0, 0, 0, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'W':
    {
        bool sevenSegArray[7] = {1, 0, 0, 1, 1, 1, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'X':
    {
        bool sevenSegArray[7] = {0, 1, 1, 1, 1, 1, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'Y':
    {
        bool sevenSegArray[7] = {1, 0, 1, 1, 1, 1, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case 'Z':
    {
        bool sevenSegArray[7] = {1, 1, 0, 1, 0, 1, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case '0':
    {
        bool sevenSegArray[7] = {1, 1, 1, 0, 1, 1, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case '1':
    {
        bool sevenSegArray[7] = {0, 0, 1, 0, 0, 1, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case '2':
    {
        bool sevenSegArray[7] = {1, 1, 0, 1, 0, 1, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case '3':
    {
        bool sevenSegArray[7] = {1, 0, 1, 1, 0, 1, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case '4':
    {
        bool sevenSegArray[7] = {0, 0, 1, 1, 1, 1, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case '5':
    {
        bool sevenSegArray[7] = {1, 0, 1, 1, 1, 0, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case '6':
    {
        bool sevenSegArray[7] = {1, 1, 1, 1, 1, 0, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case '7':
    {
        bool sevenSegArray[7] = {0, 0, 1, 0, 0, 1, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case '8':
    {
        bool sevenSegArray[7] = {1, 1, 1, 1, 1, 1, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case '9':
    {
        bool sevenSegArray[7] = {1, 0, 1, 1, 1, 1, 1};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    case '-':
    {
        bool sevenSegArray[7] = {0, 0, 0, 1, 0, 0, 0};
        this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
        break;
    }
    default:
        return;
    }
}
