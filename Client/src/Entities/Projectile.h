#pragma once
#include "Entity.h"

class Projectile : public Entity {
public:
	Entity* source;
	Uint64 lifetime;

private:
	Vector2 boxCollider{ 15, 15 };
	Vector2 enemyBoxCollider{ 15, 15 };

public:
	// Constructor
	Projectile(Entity* src, Vector2 position, float rotation, float speed, float duration = 3.0f);

	// Base Functions
	void Start() override;
	void Update() override;

	// Main Functions
	bool CheckIfTooFarAway();
	void CheckCollisions();
	void OnKill() override {};
};