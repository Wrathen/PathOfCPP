#include "CameraManager.h"
#include "GameManager.h"
#include "RenderManager.h"
#include "../Miscellaneous/Log.h"

void CameraManager::Update() {
	// Get Player position and offset it by sprite dimensions.
	Player* player = GAME.GetPlayer();
	if (!player) {
		Debug("Player not found!");
		return;
	}

	// Center the camera on player
	Vector2 pPos = player->transform.GetPosition();
	Vector2 playerCenteredCameraPosition(pPos.x - MainRenderer.SCREEN_WIDTH/2, pPos.y - MainRenderer.SCREEN_HEIGHT/2);
	transform.SetPosition(playerCenteredCameraPosition);
}