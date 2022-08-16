#pragma once
#include <cmath>

class Vector2 {
public:
    Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}
    float x, y;

    // Main Functions
    float DistanceTo(Vector2 other);
    float Dot(Vector2 other);

    // Static Functions
    static float DistanceBetween(Vector2 a, Vector2 b);
    static float DotBetween(Vector2 a, Vector2 b);

    // Operator Overloads
    Vector2& operator +=(Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2& operator -=(Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vector2& operator *=(Vector2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }
    Vector2& operator /=(Vector2& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }
    Vector2& operator *=(float value) {
        x *= value;
        y *= value;
        return *this;
    }
    Vector2& operator /=(float value) {
        x /= value;
        y /= value;
        return *this;
    }
};