#pragma once
#include "../Entities/Entity.h"
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

	// Projectiles
	unsigned int numberOfProjectiles = 1;
	float projectileSpeed = 35.00f;
	float projectileAngleMultiplier = 0.15f;
	

    // Utility
    float sizeMultiplier = 1.0f;
    float moveSpeed = 25.0f;

	// Combat
	int totalKills = 0;

    // Attacking
    float attackSpeed = 0.07f; // Attacks once every attackSpeed seconds.
    bool isAttacking = false;

	// Getters
	unsigned int GetLevel() const { return level; }
	float GetMoveSpeed() const { return moveSpeed; }
	float GetMeleePower() const { return meleePower; }
	float GetHaste() const { return haste; }
	float GetCrit() const { return crit; }
	float GetProjectileSpeed() const { return projectileSpeed; }
	float GetProjectileAngleMultiplier() const { return projectileAngleMultiplier; }
	unsigned int GetNumberOfProjectiles() const { return numberOfProjectiles; }
	float GetHealth() const { return health; }
	float GetMaxHealth() const { return maxHealth; }
	float GetAttackSpeed() const { return attackSpeed; }
	bool GetAttackingState() const { return isAttacking; }
	float GetSizeMultiplier() const { return sizeMultiplier; }

	// Setters
	void SetLevel(unsigned int value) { level = value; }
	void SetMoveSpeed(float value) { moveSpeed = value; }
	void SetMeleePower(float value) { meleePower = value; }
	void SetHaste(float value) { haste = value; }
	void SetCrit(float value) { crit = value; }
	void SetProjectileSpeed(float value) { projectileSpeed = value; }
	void SetHealth(float value) { health = value; }
	void SetMaxHealth(float value) { maxHealth = value; }
	void SetAttackSpeed(float value) { attackSpeed = value; }
	void SetAttackingState(bool value) { isAttacking = value; }
	void SetSizeMultiplier(float value) { sizeMultiplier = value; }
	void SetNumberOfProjectiles(unsigned int value) { numberOfProjectiles = value; }

	friend class Entity;
};