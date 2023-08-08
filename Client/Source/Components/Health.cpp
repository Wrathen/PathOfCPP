#include "Health.h"

void Health::Start() {}
void Health::Delete() { delete this; }

void Health::SetHealth(float value) { health = value; }
void Health::SetMaxHealth(float value) { maxHealth = value; }
void Health::SetHealthMultiplier(float value) { healthMultiplier = value; }

float Health::GetHealth() { return health * healthMultiplier; }
float Health::GetMaxHealth() { return maxHealth * healthMultiplier; }
float Health::GetBaseHealth() { return health; }
float Health::GetBaseMaxHealth() { return maxHealth; }
float Health::GetHealthMultiplier() { return healthMultiplier; }
bool inline Health::HasGuardianAngel() const { return hasGuardianAngel; }
Uint64 inline Health::GetGuardianAngelExpireTime() const { return guardianAngelExpireTime; }

void Health::SetGuardianAngel(float duration) {
	hasGuardianAngel = true;
	guardianAngelExpireTime = SDL_GetTicks64() + duration * 1000;
}

bool Health::TakeDamage(float amount) {
	if (source->isToBeDeleted) return false;
	if (hasGuardianAngel) {
		if (SDL_GetTicks64() > guardianAngelExpireTime)
			hasGuardianAngel = false;
		else return false;
	}

	// Main Logic
	health -= amount;
	if (health < 0) {
		source->OnDeath();
		return true;
	}

	return false;
}
