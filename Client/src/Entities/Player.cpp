#include "Player.h"

Player::Player() : Player("Unnamed"){}
Player::Player(std::string name) : Entity(name) {
	renderer.isFollowedByCamera = true;
	renderer.AssignTexture("assets/player.png");

	transform.SetVelocity(0.03f, 0.03f);
}

void Player::Update() {
	transform.position += transform.velocity;
}