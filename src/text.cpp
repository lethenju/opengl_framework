#include <map>
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
#include "stdio.h"
#include <string.h>

Letter::Letter(char c, float x, float y, float width, float height, Color color)
{
    // TODO Use a map of character

    c = std::toupper(c);
    int letter = 0;
    switch (c)
    {
    case 'A':
        // use the decimal representation of the seven segment
        // 0 1 1 1 1 1 1 -> 63
        letter = 63;
        break;
    case 'B':
        letter = 124;
        break;
    case 'C':
        letter = 104;
        break;
    case 'D':
        letter = 122;
        break;
    case 'E':
        letter = 109;
        break;
    case 'F':
        letter = 45;
        break;
    case 'G':
        letter = 117;
        break;
    case 'H':
        letter = 60;
        break;
    case 'I':
        letter = 16;
        break;
    case 'J':
        letter = 114;
        break;
    case 'K':
        letter = 61;
        break;
    case 'L':
        letter = 100;
        break;
    case 'M':
        letter = 57;
        break;
    case 'N':
        letter = 56;
        break;
    case 'O':
        letter = 120;
        break;
    case 'P':
        letter = 47;
        break;
    case 'Q':
        letter = 31;
        break;
    case 'R':
        letter = 40;
        break;
    case 'S':
        letter = 93;
        break;
    case 'T':
        letter = 108;
        break;
    case 'U':
        letter = 118;
        break;
    case 'V':
        letter = 112;
        break;
    case 'W':
        letter = 78;
        break;
    case 'X':
        letter = 62;
        break;
    case 'Y':
        letter = 94;
        break;
    case 'Z':
        letter = 107;
        break;
    case '0':
        letter = 119;
        break;
    case '1':
        letter = 18;
        break;
    case '2':
        letter = 107;
        break;
    case '3':
        letter = 91;
        break;
    case '4':
        letter = 30;
        break;
    case '5':
        letter = 93;
        break;
    case '6':
        letter = 125;
        break;
    case '7':
        letter = 19;
        break;
    case '8':
        letter = 127;
        break;
    case '9':
        letter = 95;
        break;
    case '-':
        letter = 8;
        break;
    default:
        letter = 0;
    }
    
    bool sevenSegArray[7];
    for (int i = 6; i >= 0; i--) {
        sevenSegArray[i] = letter%2 != 0;
        letter = letter/2;
    }
    printf("\n");

    this->repr = new SevenSegment(sevenSegArray, x, y, width, height, color);
}


Text::Text(const char* text, float x, float y, float letter_width, float letter_height, float space_between_letters, Color color) {
    int size = strlen(text);
    float x_letter_position = x;
    for (int i = 0; i < size; i++) {
        this->push_back(Letter(*(text+i),x_letter_position, y, letter_width, letter_height, color));
        x_letter_position += letter_width + space_between_letters;
    }
}