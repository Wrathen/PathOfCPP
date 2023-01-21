#include "Rect.h"
#include "Point.h"

bool Rect::Intersects(Rect& other) {
	Point leftTop(x, y);
	Point leftBottom(x, y + h);
	Point rightTop(x + w, y);
	Point rightBottom(x + w, y + h);
	return leftTop.Intersects(other) || leftBottom.Intersects(other) ||
		rightTop.Intersects(other) || rightBottom.Intersects(other);
}