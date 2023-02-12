#include "Animator.h"

// Base Functions
void Animator::Start() { 
    sourceRenderer = &source->renderer;
    if (!sourceRenderer) Warn("SpriteRenderer Component not found!");
}
void Animator::Delete() { delete this; }

// Main Functions
void Animator::Add(Animation anim) {
    anim.onSpriteChanged = [this] { this->OnSpriteChanged(); };
    anim.onAnimationEnded = [this] { this->OnAnimationEnded(); };

    map.emplace(anim.name, anim);
    if (!currentAnimation) Play(anim.name);
}
void Animator::Play(std::string animName, bool _forceAnimationCompletion) {
    if (!canSkipCurrentAnimation) return;
    if (currentAnimation && currentAnimation->name == animName) return;
    if (map.count(animName) == 0) { Warn("Animation Not Found!"); return; }

    if (currentAnimation) currentAnimation->Reset();
    currentAnimation = &map[animName];

    canSkipCurrentAnimation = !_forceAnimationCompletion;
    OnAnimationChanged();
}
void Animator::SetSpeed(float multiplier) {
    if (multiplier == 0.0) return;
    if (!currentAnimation) return;

    speedMultiplier = multiplier;
    currentAnimation->speedMultiplier = multiplier;
}
void Animator::Update() { if (currentAnimation) currentAnimation->Update(); }

// Events
void Animator::OnSpriteChanged() {
    if (!sourceRenderer) return;
    int x = currentAnimation->currentX;
    int y = currentAnimation->currentY;
    int w = currentAnimation->spriteWidth;
    int h = currentAnimation->spriteHeight;

    sourceRenderer->SetWidth(w);
    sourceRenderer->SetHeight(h);
    sourceRenderer->SetSourceOffset(x * w, y * h);

    //Debug("Playing Animation " + currentAnimation->name + ", drawing " + std::to_string(currentAnimation->currentX) + "," + std::to_string(currentAnimation->currentY));
}
void Animator::OnAnimationChanged() {
    SetSpeed(speedMultiplier);
    OnSpriteChanged();
}
void Animator::OnAnimationEnded() {
    canSkipCurrentAnimation = true;
    // Assuming all animators have an 'Idle' animation 
    // attached and it's a looped animation.
    //Play("Idle"); 
}