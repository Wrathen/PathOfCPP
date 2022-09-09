#pragma once
#include "Entity.h"

class Projectile : public Entity {
public:
	Projectile(Entity* src, Vector2 position, float rotation, float speed, float duration = 3.0f);

	// Base Functions
	void Start() override;
	void Update() override;

	// Main Functions
	void CheckCollisions();
	void OnKill() override {};

	// Members
	Entity* source;
	Uint64 lifetime;
};