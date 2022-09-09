#pragma once
class Stats {
public:
    // General Stats
    unsigned int level = 1;
    float health = 100.0f;
    float maxHealth = 100.0f;

    // Attributes
    int strength = 24;
    int dexterity = 27;
    int intelligence = -6;

    // Offensive
    unsigned int numberOfProjectiles = 1;
    float meleePower = 5;
    float haste = 0;
    float crit = 0;

    // Utility
    float sizeMultiplier = 1.0f;
    float moveSpeed = 15.0f;
    float projectileSpeed = 35.00f;

    // Attacking
    unsigned long long nextAttackTick = 0;
    float attackSpeed = 0.07f; // Attacks once every attackSpeed seconds.
    bool isAttacking = false;
};