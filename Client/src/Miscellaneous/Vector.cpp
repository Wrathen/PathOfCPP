#include "Vector.h"

float Vector2::DistanceTo(Vector2 other) { return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2)); }
float Vector2::Dot(Vector2 other) { return other.x * x + other.y * y; }
float Vector2::DistanceBetween(Vector2 a, Vector2 b) { return a.DistanceTo(b); }
float Vector2::DotBetween(Vector2 a, Vector2 b) { return a.Dot(b); }