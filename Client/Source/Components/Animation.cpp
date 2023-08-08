#include "Animation.h"

Animation::Animation() : Animation("UNDEFINED_ANIMATION") {}
Animation::Animation(std::string _name, int _eachClipLengthMS, int _spriteWidth, int _spriteHeight,
    int _minCellX, int _minCellY, int _maxCellX, int _maxCellY, bool _isLoop) {
    name = _name;
    lengthMS = _eachClipLengthMS;
    spriteWidth = _spriteWidth;
    spriteHeight = _spriteHeight;
    minCellX = _minCellX;
    minCellY = _minCellY;
    maxCellX = _maxCellX;
    maxCellY = _maxCellY;
    isLoop = _isLoop;

    currentX = minCellX;
    currentY = minCellY;

    if (minCellX > maxCellX || minCellY > maxCellY)
        Warn("Animation: Min Boundaries can not be higher than Max Boundaries.");
}

void Animation::Reset() {
    speedMultiplier = 1.0f;
    currentX = minCellX;
    currentY = minCellY;
    isRunning = true;
}
void Animation::Update() {
    if (!isRunning || timer.GetTimeMS() < (lengthMS / speedMultiplier)) return;

    if (++currentX > maxCellX) {
        if (++currentY > maxCellY) {
            if (!isLoop) isRunning = false;
            if (onAnimationEnded) onAnimationEnded();

            currentY = minCellY;
        }

        currentX = minCellX;
    }

    if (onSpriteChanged) onSpriteChanged();
    timer.Reset();
}