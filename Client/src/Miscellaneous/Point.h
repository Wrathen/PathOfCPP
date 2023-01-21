#pragma once
#include "Rect.h"

class Point {
public:
	int x;
	int y;
	Point(int _x, int _y) : x(_x), y(_y) {}

	bool Intersects(Rect& other);
};