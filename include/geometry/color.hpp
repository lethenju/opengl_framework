#pragma once
class Color
{
public:
	Color() {
		this->r = 0;
		this->v = 0;
		this->b = 0;
	};
	Color(float r, float v, float b) {
		this->r = r;
		this->v = v;
		this->b = b;
	};
	float r;
	float v;
	float b;
};

