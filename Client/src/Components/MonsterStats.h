#pragma once
#include "Stats.h"

enum class MonsterRarity {
    Common = 0,
    Magic = 1,
    Rare = 2,
    Unique = 3
};

class MonsterStats : public Stats {
public:
    MonsterRarity rarity = MonsterRarity::Common;
    unsigned int level = 1;

    float meleePower = 5;
    float haste = 0;
    float crit = 0;
    float attackSpeed = 3.20f; // Attacks once every attackSpeed seconds.
};