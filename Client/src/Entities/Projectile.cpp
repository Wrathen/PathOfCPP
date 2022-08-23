#include "Projectile.h"

Projectile::Projectile(Entity* src, Vector2 position, float rotation, float speed, float duration) : Entity("assets/arrow.png", "Arrow") {
	source = src;

	Vector2 velocity = Vector2::FromAngle(rotation) * speed;
	transform.SetVelocity(velocity);
	transform.SetPosition(position);
	transform.SetRotation(rotation);

	lifetime = SDL_GetTicks64() + static_cast<int>(duration * 1000);
}

void Projectile::Update() {
	transform.Move();
	CheckCollisions();

	Uint64 ticks = SDL_GetTicks64();
	if (ticks > lifetime) Delete();
}

void Projectile::CheckCollisions() {}