#pragma once
#include "Component.h"
class Stats: public Component {
public:
    // General Stats
    unsigned int level = 1;
    float health = 100.0f;
    float maxHealth = 100.0f;

	// Buffs
	bool hasHeadHunter = true;

	// Player-only --> will change the structure later
	float xp = 0;
	float maxXP = 1;

    // Attributes
    int strength = 24;
    int dexterity = 27;
    int intelligence = -6;

    // Offensive
    float attackPower = 5;
    float haste = 0;
    float critChance = 10.0f;
	float critMultiplier = 1.0f;
	float versatility = 0;

	// Projectiles
	unsigned int numberOfProjectiles = 1;
	float projectileSpeed = 35.00f;
	float projectileAngleMultiplier = 0.15f;
	int piercingAmount = 1;
	
    // Utility
    float sizeMultiplier = 1.0f;
    float moveSpeed = 25.0f;

	// Combat
	int totalKills = 0;

    // Attacking
    float attackSpeed = 0.07f; // Attacks once every attackSpeed seconds.
    bool isAttacking = false;

	// Getters
	unsigned int inline GetNumberOfProjectiles() const { return numberOfProjectiles; }
	unsigned int inline GetLevel() const { return level; }
	float inline GetXP() const { return xp; }
	float inline GetMaxXP() const { return maxXP; }
	float inline GetMoveSpeed() const { return moveSpeed; }
	float inline GetAttackPower() const { return attackPower; }
	float inline GetHaste() const { return haste; }
	float inline GetCritChance() const { return critChance; }
	float inline GetCritMultiplier() const { return critMultiplier; }
	float inline GetVersatility() const { return versatility; }
	float inline GetProjectileSpeed() const { return projectileSpeed; }
	float inline GetProjectileAngleMultiplier() const { return projectileAngleMultiplier; }
	float inline GetHealth() const { return health; }
	float inline GetMaxHealth() const { return maxHealth; }
	float inline GetAttackSpeed() const { return attackSpeed; }
	float inline GetSizeMultiplier() const { return sizeMultiplier; }
	float inline GetDamageAmount() const { return attackPower; }
	int inline GetPiercingAmount() const { return piercingAmount; }
	bool inline GetAttackingState() const { return isAttacking; }

	// Setters
	void SetLevel(unsigned int value) { level = value; }
	void SetXP(float value) { xp = value; }
	void SetMaxXP(float value) { maxXP = value; }
	void SetMoveSpeed(float value) { moveSpeed = value; }
	void SetAttackPower(float value) { attackPower = value; }
	void SetHaste(float value) { haste = value; }
	void SetCritChance(float value) { critChance = value; }
	void SetCritMultiplier(float value) { critMultiplier = value; }
	void SetProjectileSpeed(float value) { projectileSpeed = value; }
	void SetHealth(float value) { health = value; }
	void SetMaxHealth(float value) { maxHealth = value; }
	void SetAttackSpeed(float value) { attackSpeed = value; }
	void SetAttackingState(bool value) { isAttacking = value; }
	void SetSizeMultiplier(float value) { sizeMultiplier = value; }
	void SetNumberOfProjectiles(unsigned int value) { numberOfProjectiles = value; }
	void SetPiercingAmount(int value) { piercingAmount = value; }

	// Enforced Method by Component Base Class
	void Start() {}
};