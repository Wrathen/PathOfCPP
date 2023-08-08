#pragma once
#include <string>
#include <functional>
#include "../Miscellaneous/Timer.h"
#include "../Miscellaneous/Log.h"

class Animation {
public:
    std::string name = "Idle";
    int lengthMS = 333;
    float speedMultiplier = 1.0f;

    int spriteWidth = 32;
    int spriteHeight = 32;
    int currentX = 0;
    int currentY = 0;
    int minCellX = 0;
    int minCellY = 0;
    int maxCellX = 4;
    int maxCellY = 4;

    Timer timer;
    bool isRunning = true;
    bool isLoop = false;

    std::function<void()> onSpriteChanged;
    std::function<void()> onAnimationEnded;

    Animation();
    // Min [Inclusive], Max [Exclusive]
    Animation(std::string _name, int _eachClipLengthMS = 333, int _spriteWidth = 32, int _spriteHeight = 32,
        int _minCellX = 0, int _minCellY = 0, int _maxCellX = 4, int _maxCellY = 4, bool _isLoop = false);

    void Reset();
    void Update();
};