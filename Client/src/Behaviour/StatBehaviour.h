#pragma once
#include "../Components/Stats.h"
#include "../Miscellaneous/Log.h"
#include "../Miscellaneous/Random.h"

class StatBehaviour {
public:
	void TakeDamage(float dmg);
	void Die();

	// Getters
	const Stats* GetStats() const { return stats; }
	unsigned int GetLevel() const { return stats->level; }
	float GetMoveSpeed() const { return stats->moveSpeed; }
	float GetMeleePower() const { return stats->meleePower; }
	float GetHaste() const { return stats->haste; }
	float GetCrit() const { return stats->crit; }
	float GetProjectileSpeed() const { return stats->projectileSpeed; }
	float GetHealth() const { return stats->health; }
	float GetMaxHealth() const { return stats->maxHealth; }
	unsigned long long GetNextAttackTick() const { return stats->nextAttackTick; }
	float GetAttackSpeed() const { return stats->attackSpeed; }
	bool GetAttackingState() const { return stats->isAttacking; }
	float GetSizeMultiplier() const { return stats->sizeMultiplier; }
	unsigned int GetNumberOfProjectiles() const { return stats->numberOfProjectiles; }

	// Setters
	void SetLevel(unsigned int value) { stats->level = value; }
	void SetMoveSpeed(float value) { stats->moveSpeed = value; }
	void SetMeleePower(float value) { stats->meleePower = value; }
	void SetHaste(float value) { stats->haste = value; }
	void SetCrit(float value) { stats->crit = value; }
	void SetProjectileSpeed(float value) { stats->projectileSpeed = value; }
	void SetHealth(float value) { stats->health = value; }
	void SetMaxHealth(float value) { stats->maxHealth = value; }
	void SetNextAttackTick(unsigned long long value) { stats->nextAttackTick = value; }
	void SetAttackSpeed(float value) { stats->attackSpeed = value; }
	void SetAttackingState(bool value) { stats->isAttacking = value; }
	void SetSizeMultiplier(float value) { stats->sizeMultiplier = value; }
	void SetNumberOfProjectiles(unsigned int value) { stats->numberOfProjectiles = value; }

protected:
	StatBehaviour();
	~StatBehaviour();

private:
	Stats* stats;
};