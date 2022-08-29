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
    float meleePower = 5;
    float haste = 0;
    float crit = 0;

    // Utility
    float moveSpeed = 15.0f;
    float projectileSpeed = 35.00f;

    // Attacking
    unsigned long long nextAttackTick = 0;
    float attackSpeed = 0.07f; // Attacks once every attackSpeed seconds.
    bool isAttacking = false;

    // I am having an internal debate with myself, that should we have Methods in here?
    // Or how else can we approach this. Like for ex: TakeDamage()
    // Does that method belong here? Or some other class I should implement like, IDK, EntityBehaviour?
    // Or EntityStatBehaviour?
    // But that just makes things worse like
    // Imagine typing, entity->entityStatBehaviour.TakeDamage(dmg);
    // Look how bad it looks, just to damage an entity.
    // Right now it'd look like, entity->GetStats()->TakeDamage(dmg);
    // I don't want such methods to be in the main Entity class.
    // Entity is like an interface, not a behavioural class.
    // Maybe make Entity a subclass of StatBehaviour class
    // Thus, inheriting StatBehaviour class methods.
    // Then we can do entity.TakeDamage(dmg);
};