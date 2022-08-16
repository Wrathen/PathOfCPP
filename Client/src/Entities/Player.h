#pragma once
#include "Entity.h"
#include "../Components/SpriteRenderer.h"
#include "../Components/PlayerStats.h"
#include "../Components/Transform.h"

class Player : public Entity {
public:
    Player();
    Player(std::string name);

    std::string ToString() {
        if (this == nullptr) return "This entity has already been deleted. What are you doing?!";
        return "A level " + std::to_string(stats.level) + " " + name + " with GUID: " + std::to_string(guid);
    }

    void Update();
private:
    PlayerStats stats;
};