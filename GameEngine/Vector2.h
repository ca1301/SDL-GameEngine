#pragma once
#include <math.h>
class Vector2
{

public:
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);
	float length() { return sqrt(x * x + y * y); }

};

