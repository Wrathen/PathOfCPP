#pragma once
#include "Entity.h"
#include "Components/TextRenderer.h"
#include "Components/Health.h"
#include "Components/HealthBar.h"
#include "Components/Collision/BoxCollider.h"
#include "Behaviour/AI/MoveTowardsTarget.h"

enum class MonsterRarity {
    Common = 0,
    Magic = 1,
    Rare = 2,
    Unique = 3,
    Count = 4
};

class Monster: public Entity {
public:
    // Components
    Stats* CStats = nullptr;
    Health* CHealth = nullptr;
    HealthBar* CHealthBar = nullptr;
    MoveTowardsTarget* CMoveTowardsTarget = nullptr;
    BoxCollider* CCollider = nullptr;

    // Other Members
    TextRenderer nameTag;
    MonsterRarity rarity = MonsterRarity::Common;
    float lootChance = 4.12f;

    // Base Functions
    void Start() override;
    void Update() override;
    void Render() override;

    // Main Functions
    void OnKill() override {}
    void OnDeath() override;

    // Utility Functions
    std::string ToString() override {
        if (!this) return "This entity has already been deleted. What are you doing?!";
        return "A level " + std::to_string(CStats->GetLevel()) + " " + name + " monster with GUID: " + std::to_string(guid);
    }

protected:
    Monster() = delete;
    Monster(std::string name);
    Monster(std::string texturePath, std::string name);
    ~Monster();
};