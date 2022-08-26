#include "Player.h"
#include "Projectile.h"
#include "../Miscellaneous/Log.h"

Player::Player(std::string name) : Entity("assets/sprites/player.png", name) { Start(); }

void Player::Start() {
	stats = new PlayerStats();
	stats->moveSpeed = 45.0f;
}

void Player::Update() {
	transform.Move(transform.velocity.Normalize(), stats->moveSpeed);

	if (stats->isAttacking && SDL_GetTicks64() > stats->nextAttackTick) {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		Vector2 mousePos(mouseX, mouseY);
		ShootArrow(mousePos);

		stats->nextAttackTick = SDL_GetTicks64() + (stats->attackSpeed * 1000);
	}
}

void Player::ShootArrow(const Vector2& targetPos) {
	float rotation = Vector2::AngleBetween(transform.GetScreenPosition(), targetPos);
	new Projectile(this, transform.GetPosition(), rotation, stats->projectileSpeed);
}