#pragma once
#include <unordered_map>
#include "Component.h"
#include "Animation.h"

class Animator : public Component {
public:
    std::unordered_map<std::string, Animation> map;
    SpriteRenderer* sourceRenderer = nullptr;
    Animation* currentAnimation = nullptr;
    bool canSkipCurrentAnimation = true;
    float speedMultiplier = 1.0f;

    // Base Functions
    void Start();
    void Delete();

    // Main Functions
    void Add(Animation anim);
    void Play(std::string animName, bool _forceAnimationCompletion = false);
    void SetSpeed(float multiplier);
    void Update();

    // Utility Functions
    unsigned int GetFullCycleLengthInMilliseconds();

    // Events
    void OnSpriteChanged();
    void OnAnimationChanged();
    void OnAnimationEnded();
};