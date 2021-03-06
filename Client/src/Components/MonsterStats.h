#pragma once
#include "Stats.h"

class MonsterStats : public Stats {
public:
    unsigned int level = 1;
    float meleePower = 5;
    float haste = 0;
    float crit = 0;
    float attackSpeed = 3.20f; // Attacks once every attackSpeed seconds.
};