#pragma once
#include "Entity.h"
#include "../Components/HealthBar.h"

class Player : public Entity {
public:
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

    // Utility Functions
    std::string ToString() override {
        if (!this) return "This entity has already been deleted. What are you doing?!";
        return "A level " + std::to_string(GetLevel()) + " " + name + " with GUID: " + std::to_string(guid);
    }

    HealthBar* healthBar;
};