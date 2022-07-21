#pragma once
#include "Entity.h"
#include "Components/SpriteRenderer.h"
#include "Components/MonsterStats.h"
#include "Components/Transform.h"

class Monster : public Entity {
public:
    Monster();
    Monster(std::string name);
    Monster(std::string texturePath, std::string name);

    std::string ToString() {
        if (this == nullptr) return "This entity has already been deleted. What are you doing?!";
        return "A level " + std::to_string(stats.level) + " " + name + " with GUID: " + std::to_string(guid);
    }
private:
    MonsterStats stats;
};