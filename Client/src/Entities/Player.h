#pragma once
#include "Entity.h"
#include "../Components/HealthBar.h"
#include "../Miscellaneous/Timer.h"

class Player : public Entity {
public:
    Stats* stats;
    HealthBar* healthBar;
    Timer attackTimer;

    // Constructor & Deconstructor
    Player(std::string name);
    ~Player() {
        healthBar->Delete();
        healthBar = nullptr;
    }

    // Base Functions
    void Start() override;
    void Update() override;

    // Main Functions
    void ShootArrow(const Vector2& targetPos);
    void OnKill() override;
    void OnDeath() override;
    void FUN_Headhunter();

    // Utility Functions
    std::string ToString() override {
        if (!this) return "This entity has already been deleted. What are you doing?!";
        return "A level " + std::to_string(stats->GetLevel()) + " " + name + " with GUID: " + std::to_string(guid);
    }
};