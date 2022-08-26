#pragma once
#include "Entity.h"
#include "../Components/MonsterStats.h"
#include "../Behaviour/AI/MoveTowardsTarget.h"

class Monster: public Entity {
public:
    // Base Functions
    void Start() override;
    void Update() override;

    // Main Functions
    MonsterStats* GetStats() override { return stats; }

    // Utility Functions
    std::string ToString() override {
        if (!this) return "This entity has already been deleted. What are you doing?!";
        return "A level " + std::to_string(stats->level) + " " + name + " with GUID: " + std::to_string(guid);
    }

    MonsterStats* stats;
    MoveTowardsTarget moveTowardsTarget;

protected:
    Monster() = delete;
    Monster(std::string name);
    Monster(std::string texturePath, std::string name);
    ~Monster() { delete stats; stats = nullptr; }
};