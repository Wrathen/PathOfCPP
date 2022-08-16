#pragma once
#include "../Miscellaneous/Vector.h"

class Transform {
public:
    Vector2 position = Vector2(0, 0);
    Vector2 scale = Vector2(1, 1);
    Vector2 velocity = Vector2(0, 0);
    float rotation = 0;

    void SetPosition(float  x, float y) { position.x = x; position.y = y; }
    void SetScale(float  x, float y) { scale.x = x; scale.y = y; }
    void SetVelocity(float  x, float y) { velocity.x = x; velocity.y = y; }
    void SetPosition(const Vector2& vec) { position.x = vec.x; position.y = vec.y; }
    void SetScale(const Vector2& vec) { scale.x = vec.x; scale.y = vec.y; }
    void SetVelocity(const Vector2& vec) { velocity.x = vec.x; velocity.y = vec.y; }
    void SetRotation(float x) { rotation = x; }
};