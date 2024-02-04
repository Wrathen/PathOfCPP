#include "Rect.h"

CollisionResult Rect::Intersects(const Rect& other) const {
	return IntersectsRect(this->x, this->y, this->w, this->h, other.x, other.y, other.w, other.h);
}

// Static Functions
bool Rect::IntersectsPoint(int x1, int y1, int w, int h, int x2, int y2) {
	return x1 < x2 && x1 + w > x2 && y1 < y2 && y1 + h > y2;
}
CollisionResult Rect::IntersectsRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	CollisionResult result;

	if (Rect::IntersectsPoint(x1, y1, w1, h1, x2, y2)) { // Second Rect's left top point
		result |= CollisionResult::LEFT;
		result |= CollisionResult::TOP;
	}
	if (Rect::IntersectsPoint(x1, y1, w1, h1, x2 + w2, y2)) { // Second Rect's right top point
		result |= CollisionResult::RIGHT;
		result |= CollisionResult::TOP;
	}
	if (Rect::IntersectsPoint(x1, y1, w1, h1, x2, y2 + h2)) { // Second Rect's left bottom point
		result |= CollisionResult::LEFT;
		result |= CollisionResult::BOTTOM;
	}
	if (Rect::IntersectsPoint(x1, y1, w1, h1, x2 + w2, y2 + h2)) { // Second Rect's right bottom point
		result |= CollisionResult::RIGHT;
		result |= CollisionResult::BOTTOM;
	}

	return result;
}