#pragma once
#include "Stats.h"

class PlayerStats : public Stats {
public:
    // General Stats
    unsigned int level = 1;
    int strength = 24;
    int dexterity = 27;
    int intelligence = -6;

    float meleePower = 5;
    float haste = 0;
    float crit = 0;
    float projectileSpeed = 35.00f;

    // Attacking
    Uint64 nextAttackTick = 0;
    float attackSpeed = 0.07f; // Attacks once every attackSpeed seconds.
    bool isAttacking = false;
};