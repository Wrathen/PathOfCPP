#include "Gambler.h"
#include "../../Managers/InputManager.h"
#include "../../Managers/GameManager.h"
#include "../../Game/Item/Item.h"
#include "../../Miscellaneous/Random.h"

Gambler::Gambler(std::string name): NPC("assets/sprites/monsters/111.png", "Gambler " + name) {
	renderer.SetScale(0.05f, 0.05f);
}

void Gambler::Update() {
	Super::Update();

	if (IsPlayerNearby() && InputMgr.IsKeyHeld(SDLK_e))
		PurchaseRandomItem();
}

void Gambler::OnPlayerNearby() {}
void Gambler::OnPlayerAway() {}

void Gambler::PurchaseRandomItem() {
	auto player = GAME.GetPlayer();

	if (true/*player->goldAmount >= 0*/) {
		Item::DropItem(RandomInt(1, player->CStats->GetLevel()), player->transform.GetPosition() + RandomVector(150));
		player->goldAmount -= 17;
	}
}