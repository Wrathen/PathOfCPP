#pragma once
class Stats {
public:
    // General Stats
    unsigned int level = 1;
    float moveSpeed = 15.0f;

    float meleePower = 5;
    float haste = 0;
    float crit = 0;
    float projectileSpeed = 35.00f;

    float health = 100.0f;
    float maxHealth = 100.0f;

    // Attacking
    unsigned long long nextAttackTick = 0;
    float attackSpeed = 0.07f; // Attacks once every attackSpeed seconds.
    bool isAttacking = false;
};