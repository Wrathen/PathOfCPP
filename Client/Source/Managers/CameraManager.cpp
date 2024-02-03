#include "CameraManager.h"
#include "GameManager.h"
#include "RenderManager.h"
#include "Game/Component/Components.h"

void CameraManager::Update() {
	// Get Player position and offset it by sprite dimensions.
	Core::Entity player = GAME.GetLocalPlayer();
	if (!player) 
		return;

	auto& C_Transform = player.GetComponent<TransformComponent>();

	// Center the camera on player.
	Vector2 pPos = C_Transform.position;
	position.x = pPos.x - MainRenderer.SCREEN_WIDTH / 2;
	position.y = pPos.y - MainRenderer.SCREEN_HEIGHT / 2;

	// Clamp the camera position inside the map.
	position.x = position.x < -2000 ? -2000 : position.x > 0 ? 0 : position.x;
	position.y = position.y < -2000 ? -2000 : position.y > 900 ? 900 : position.y;
}