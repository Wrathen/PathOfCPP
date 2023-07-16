#include "NPC.h"
#include "../../Managers/GameManager.h"

NPC::NPC(std::string name) : Entity(name) { Start(); }
NPC::NPC(std::string texturePath, std::string name) : Entity(texturePath, name) { Start(); }
NPC::~NPC() {}

// Base Functions
void NPC::Start() {
	transform.SetScale(4, 4);

	// Name Tag
	nameTag.AssignTransform(&transform);
	nameTag.SetText(name, SDL_Color{ 255, 255, 255 });
	nameTag.SetOffset(0, -75);
	nameTag.SetFontSize(10);
	nameTag.shouldDrawCentered = true;
}
void NPC::Update() {
	float distanceToPlayer = Vector2::DistanceBetween(GAME.GetPlayer()->transform.GetPosition(), transform.GetPosition());
	if (!isPlayerNearby && distanceToPlayer < nearbyThreshold) {
		//GAME.DrawRect(transform.GetScreenPosition() - Vector2(50, 50), 100, 100);
		isPlayerNearby = true;
		OnPlayerNearby();
	}
	else if (isPlayerNearby && distanceToPlayer > nearbyThreshold) {
		isPlayerNearby = false;
		OnPlayerAway();
	}
}
void NPC::Render() {
	renderer.Render();
	nameTag.Render();
}
void NPC::OnKill() {}
void NPC::OnDeath() {}