#include "Vector.h"

// Methods
float Vector2::DistanceTo(Vector2 other) const { return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2)); }
float Vector2::Dot(Vector2 other) const { return other.x * x + other.y * y; }
float Vector2::Magnitude() const { return sqrt(x * x + y * y); }
Vector2 Vector2::Normalize() { float mag = Magnitude(); if (mag == 0) return Vector2(0.0f, 0.0f); return Vector2(x / mag, y / mag); }

// Static Functions
float Vector2::DistanceBetween(Vector2 a, Vector2 b) { return a.DistanceTo(b); }
float Vector2::DotBetween(Vector2 a, Vector2 b) { return a.Dot(b); }
Vector2 Vector2::DirectionBetween(Vector2 a, Vector2 b) { return Vector2(b.x - a.x, b.y - a.y); }
float Vector2::AngleBetween(Vector2 a, Vector2 b) { return atan2(b.y - a.y, b.x - a.x); }
