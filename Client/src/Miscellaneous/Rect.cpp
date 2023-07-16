#include "Rect.h"
#include "Point.h"

bool Rect::Intersects(const Rect& other) const {
	Point leftTop(x, y);
	Point leftBottom(x, y + h);
	Point rightTop(x + w, y);
	Point rightBottom(x + w, y + h);

	return leftTop.Intersects(other) || leftBottom.Intersects(other) ||
		rightTop.Intersects(other) || rightBottom.Intersects(other);
}

// Static Functions
bool Rect::IntersectsPoint(int x1, int y1, int w, int h, int x2, int y2) {
	return x1 < x2 && x1 + w > x2 && y1 < y2 && y1 + h > y2;
}
bool Rect::IntersectsRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	return IntersectsPoint(x1, y1, w1, h1, x2, y2) || // left top
		IntersectsPoint(x1, y1, w1, h1, x2 + w2, y2) || // right top
		IntersectsPoint(x1, y1, w1, h1, x2, y2 + h2) || // left bottom
		IntersectsPoint(x1, y1, w1, h1, x2 + w2, y2 + h2); // right bottom
}