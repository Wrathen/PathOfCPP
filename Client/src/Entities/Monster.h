#pragma once
#include "Entity.h"
#include "Components/MonsterRenderer.h"
#include "Components/MonsterStats.h"
#include "Components/Transform.h"

class Monster : public Entity {
public:
    Monster();
    Monster(std::string name);
private:
    Transform transform;
    MonsterRenderer renderer;
    MonsterStats stats;
};