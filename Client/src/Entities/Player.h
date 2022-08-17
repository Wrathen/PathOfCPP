#pragma once
#include "Entity.h"
#include "../Components/PlayerStats.h"

class Player : public Entity {
public:
    Player(std::string name);
    ~Player() { delete stats; stats = nullptr; }

    // Base Functions
    void Start() override;
    void Update() override;

    // Main Functions
    Stats* GetStats() override { return stats; }

    // Utility Functions
    std::string ToString() override {
        if (!this) return "This entity has already been deleted. What are you doing?!";
        return "A level " + std::to_string(stats->level) + " " + name + " with GUID: " + std::to_string(guid);
    }

    PlayerStats* stats;
};