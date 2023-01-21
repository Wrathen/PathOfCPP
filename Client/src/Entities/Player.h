#pragma once
#include "Entity.h"
#include "../Components/TextRenderer.h"
#include "../Components/HealthBar.h"
#include "../Miscellaneous/Timer.h"

class Player : public Entity {
public:
    TextRenderer nameTag;
    Stats* stats;
    HealthBar* healthBar;
    Timer attackTimer;
    int goldAmount;

    // Constructor & Deconstructor
    Player(std::string name);
    ~Player() {
        healthBar->Delete();
        healthBar = nullptr;
    }

    // Base Functions
    void Start() override;
    void Update() override;
    void Render() override;

    // Main Functions
    void ShootArrow(const Vector2& targetPos);
    void LevelUp();
    void GainXP(float value);
    void FUN_Headhunter();

    // Events
    void OnKill() override;
    void OnDeath() override;

    // Utility Functions
    std::string ToString() override {
        if (!this) return "This entity has already been deleted. What are you doing?!";
        return "A level " + std::to_string(stats->GetLevel()) + " " + name + " with GUID: " + std::to_string(guid);
    }
};