#pragma once
#include "Component.h"

class Health: public Component {
private:
	float health = 1;
	float maxHealth = 1;
	float healthMultiplier = 1.0f;

	bool hasGuardianAngel = false;
	Uint64 guardianAngelExpireTime = 0.0f;

public:
	void Start() override;
	void Delete();

	void SetHealth(float value);
	void SetMaxHealth(float value);
	void SetHealthMultiplier(float value);

	float GetHealth();
	float GetMaxHealth();
	float GetBaseHealth();
	float GetBaseMaxHealth();
	float GetHealthMultiplier();

	void SetGuardianAngel(float duration);
	bool inline HasGuardianAngel() const;
	Uint64 inline GetGuardianAngelExpireTime() const;

	// Returns true if died.
	bool TakeDamage(float amount);
};