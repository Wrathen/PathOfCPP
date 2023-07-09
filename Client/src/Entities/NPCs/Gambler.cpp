#include "Gambler.h"
#include "../../Managers/InputManager.h"
#include "../../Managers/GameManager.h"
#include "../../Game/Item/Item.h"
#include "../../Miscellaneous/Random.h"

Gambler::Gambler(std::string name) :
	NPC("assets/sprites/monsters/zombie/rare.png", "Gambler " + name) {}

void Gambler::Update() {
	Super::Update();

	if (isPlayerNearby && InputMgr.IsKeyPressed(SDLK_e))
		PurchaseRandomItem();
}

void Gambler::OnPlayerNearby() {}
void Gambler::OnPlayerAway() {}

void Gambler::PurchaseRandomItem() {
	auto player = GAME.GetPlayer();

	if (player->goldAmount > 10) {
		Item::DropItem(RandomInt(300), player->transform.GetPosition() + Vector2::RandomVector(-150, 150));
		player->goldAmount -= 10;
	}
}