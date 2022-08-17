#include "Monster.h"
#include "../Managers/GameManager.h"
#include "../Miscellaneous/Random.h"

Monster::Monster() : Monster("Unnamed") {}
Monster::Monster(std::string name) : Monster("assets/monster.png", name) {}
Monster::Monster(std::string texturePath, std::string name): Entity(texturePath, name) { Start(); }

void Monster::Start() {
	stats = new MonsterStats();
	moveTowardsTarget.SetSource(this);
	moveTowardsTarget.SetTarget((Entity*)GAME.GetPlayer());

	stats->moveSpeed = 8.0f;

	// [To:Do] Delete--Debug
	int randx = RandomInt(3778) - 3778 / 2;
	int randy = RandomInt(3778) - 3778 / 2;

	GAME.Debug(std::to_string(randx) + ", " + std::to_string(randy));
	transform.SetPosition(randx, randy);
}

void Monster::Update() {
	moveTowardsTarget.Update();
}