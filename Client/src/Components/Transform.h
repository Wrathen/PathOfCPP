#pragma once
#include "../Miscellaneous/Vector.h"

class Transform {
public:
    Vector2 position = Vector2(0, 0);
    Vector2 scale = Vector2(1, 1);
    float rotation = 0;
};