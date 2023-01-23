#pragma once
#include "Entity.h"

class Projectile : public Entity {
public:
	Entity* source;
	Uint64 lifetime;

	Vector2 boxCollider{ 20, 15 };
	Vector2 enemyBoxCollider{ 70, 70 };
	int piercingAmount = 1;
	int overlappingProjectiles = 0;
	float damageAmount = 1;

	// Constructor
	Projectile(Entity* src, Vector2 position, float rotation, float speed, float duration = 3.0f);

	// Base Functions
	void Start() override;
	void Update() override;

	// Main Functions
	bool CheckIfTooFarAway();
	void CheckCollisions();
	void CheckLifetime();
	void OnKill() override {};
	void OnDeath() override {};
};