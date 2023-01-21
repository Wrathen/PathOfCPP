#include "Point.h"

bool Point::Intersects(Rect& other) {
	return x > other.x && x < other.x + other.w && y > other.y && y < other.y + other.h;
}