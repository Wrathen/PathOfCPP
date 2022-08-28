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
};