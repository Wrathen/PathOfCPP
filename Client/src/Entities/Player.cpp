#include "Player.h"
#include "Projectile.h"
#include "../Miscellaneous/Log.h"

Player::Player(std::string name) : Entity("assets/sprites/player.png", name) { Start(); }

void Player::Start() {
	SetMoveSpeed(45.0f);

	healthBar = new HealthBar(this);
	healthBar->transform.SetScale(3.5f, 3.0f);
	
	transform.SetScale(2.2f, 2.2f);

	collisionTag = EntityCollisionTag::Friendly;
}

void Player::Update() {
	transform.Move(transform.velocity.Normalize(), GetMoveSpeed());

	if (GetAttackingState() && SDL_GetTicks64() > GetNextAttackTick()) {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		Vector2 mousePos(mouseX, mouseY);
		ShootArrow(mousePos);

		SetNextAttackTick(SDL_GetTicks64() + (GetAttackSpeed() * 1000));
	}
}

void Player::ShootArrow(const Vector2& targetPos) {
	float rotation = Vector2::AngleBetween(transform.GetScreenPosition(), targetPos);
	new Projectile(this, transform.GetPosition(), rotation, GetProjectileSpeed());
}