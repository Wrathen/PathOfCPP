#include "Point.h"

bool Point::Intersects(const Rect& other) const {
	return x > other.x && x < other.x + other.w && y > other.y && y < other.y + other.h;
}