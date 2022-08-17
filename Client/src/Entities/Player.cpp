#include "Player.h"

Player::Player(std::string name) : Entity("assets/player.png", name) { Start(); }

void Player::Start() {
	stats = new PlayerStats();
	stats->moveSpeed = 45.0f;
}

void Player::Update() {
	transform.Move(transform.velocity.Normalize(), stats->moveSpeed);
}