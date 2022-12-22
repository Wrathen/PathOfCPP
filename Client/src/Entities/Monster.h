#pragma once
#include "Entity.h"
#include "../Components/HealthBar.h"
#include "../Behaviour/AI/MoveTowardsTarget.h"
#include "../Components/Collision/BoxCollider.h"

enum class MonsterRarity {
    Common = 0,
    Magic = 1,
    Rare = 2,
    Unique = 3
};

class Monster: public Entity {
public:
    MonsterRarity rarity = MonsterRarity::Common;
    MoveTowardsTarget moveTowardsTarget;
    BoxCollider* collider;
    HealthBar* healthBar;

    // Base Functions
    void Start() override;
    void Update() override;

    // Main Functions
    void OnKill() override {}

    // Utility Functions
    std::string ToString() override {
        if (!this) return "This entity has already been deleted. What are you doing?!";
        return "A level " + std::to_string(GetLevel()) + " " + name + " with GUID: " + std::to_string(guid);
    }

protected:
    Monster() = delete;
    Monster(std::string name);
    Monster(std::string texturePath, std::string name);
    ~Monster();
};