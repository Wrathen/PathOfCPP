#pragma once
#include "Entity.h"
#include "../Components/TextRenderer.h"
#include "../Components/Stats.h"
#include "../Components/HealthBar.h"
#include "../Components/Animator.h"
#include "../Components/Collision/BoxCollider.h"
#include "../Miscellaneous/Timer.h"

class Player : public Entity {
public:
    // Components
    Stats* CStats;
    Health* CHealth;
    HealthBar* CHealthBar;
    Animator* CAnimator;
    BoxCollider* CCollider;

    // Other Members
    TextRenderer nameTag;
    Timer attackTimer;
    int goldAmount;

    // Constructor & Deconstructor
    Player(std::string name);
    ~Player();

    // Base Functions
    void Start() override;
    void Update() override;
    void Render() override;

    // Main Functions
    void HandleInput();
    void Leech(float damageAmount);
    void GainXP(float value);
    void LevelUp();
    void FUN_Headhunter();

    // Events
    void OnMouseDown();
    void OnMouseUp();
    void OnLevelUp();
    void OnKill() override;
    void OnDeath() override;

    // Utility Functions
    std::string ToString() override {
        if (!this) return "This entity has already been deleted. What are you doing?!";
        return "A level " + std::to_string(CStats->GetLevel()) + " " + name + " with GUID: " + std::to_string(guid);
    }
};