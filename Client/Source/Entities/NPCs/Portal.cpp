#include "Portal.h"
#include "../../Managers/InputManager.h"
#include "../../Managers/SceneManager.h"
#include "../../Managers/GameManager.h"
#include "../../Game/Item/Item.h"
#include "../../Miscellaneous/Random.h"

Portal::Portal(const ZonePortalData& _data): data(_data), NPC("Assets/portal.png", "Portal") {
	renderer.SetScale(0.05f, 0.05f);
	nameTag.SetText(data.nextZone, SDL_Color{ 255, 255, 255 }, true);

	SetNearbyThreshold(100);
}

void Portal::Update() {
	Super::Update();

	if (IsPlayerNearby() && InputMgr.IsKeyPressed(SDLK_e))
		TeleportToNextMap();
}

void Portal::OnPlayerNearby() {}
void Portal::OnPlayerAway() {}
void Portal::TeleportToNextMap() { SceneMgr.ChangeScene(data.nextZone); }