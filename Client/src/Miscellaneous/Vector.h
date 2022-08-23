#pragma once
#include <cmath>
#include <string_view>
#include <string>

class Vector2 {
public:
    Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}
    float x, y;

    // Main Functions
    float DistanceTo(Vector2 other) const;
    float Dot(Vector2 other) const;
    float Magnitude() const;
    Vector2 Normalize();

    // Static Functions
    static float DistanceBetween(Vector2 a, Vector2 b);
    static float DotBetween(Vector2 a, Vector2 b);
    static Vector2 DirectionBetween(Vector2 a, Vector2 b);
    static float AngleBetween(Vector2 a, Vector2 b);
    static Vector2 FromAngle(float angle) { return Vector2(cos(angle), sin(angle)); }

    // Utility Functions
    std::string ToString() const { return std::string(std::to_string(x) + ", " + std::to_string(y)); }

    // Operator Overloads
    Vector2& operator +=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
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
    Vector2& operator +=(float value) {
        x += value;
        y += value;
        return *this;
    }
    Vector2& operator -=(float value) {
        x += value;
        y += value;
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
    Vector2 operator +(Vector2 value) const {
        Vector2 vec(x + value.x, y + value.y);
        return vec;
    }
    Vector2 operator -(Vector2 value) const {
        Vector2 vec(x - value.x, y - value.y);
        return vec;
    }
    Vector2 operator *(float value) const {
        Vector2 vec(x * value, y * value);
        return vec;
    }
    Vector2 operator /(float value) const {
        Vector2 vec(x / value, y / value);
        return vec;
    }
};