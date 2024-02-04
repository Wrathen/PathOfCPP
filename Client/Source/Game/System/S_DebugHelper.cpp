#include "S_DebugHelper.h"
#include "Miscellaneous/Utils.h"
#include "Game/Component/Components.h"
#include "Core/Managers/CollisionManager.h"
#include "Managers/InputManager.h"
#include "Managers/GameManager.h"

void DrawPlayerCollider() {
	auto localPlayer = Utils::GetLocalPlayer();
	auto pos = Utils::GetScreenPosition(localPlayer.GetComponent<TransformComponent>());
	Utils::FillRect((int)pos.x - 8, (int)pos.y - 8, 16, 16, { 0, 255, 0, 255 });
}
void DrawStaticColliders() {
	for (auto& data : Core::CollisionMgr.staticColliders) {
		auto colPos = Utils::GetScreenPosition(data.position);
		Utils::FillRect((int)colPos.x, (int)colPos.y, data.w, data.h, { 127, 0, 255, 0 });
	}
}
void DrawStaticCollidersSpatialHash() {
	auto localPlayer = Utils::GetLocalPlayer();
	auto pos = localPlayer.GetComponent<TransformComponent>().position;

	Rect rect{ (int)pos.x - 8 , (int)pos.y - 8, 16, 16 };
	auto nearbyColliders = Core::CollisionMgr.staticCollidersSpatialHash.Query(rect.x, rect.y, 100);
	for (auto& data : nearbyColliders) {
		auto colPos = Utils::GetScreenPosition(data.position);
		Utils::FillRect((int)colPos.x, (int)colPos.y, data.w, data.h, { 255, 0, 127, 255 });
	}
}

void HandleLocalPlayerHotkeys() {
	auto curSceneName = Core::SceneMgr.GetCurrentScene()->name;
	if (InputMgr.IsKeyPressed(SDLK_g)) {
		if (curSceneName == "Town")
			Core::SceneMgr.ChangeScene("DefiledCathedral");
		else
			Core::SceneMgr.ChangeScene("Town");
	}
}

void LogEngineBenchmark() {
	static Timer debugTimer;

	// Output Benchmarks
	if (debugTimer.GetTimeMS() > 2000) {
		GAME.benchmark.Log();
		debugTimer.Reset();
	}
}

void S_DebugHelper::Update() {
	DrawPlayerCollider();
	//DrawStaticColliders();
	DrawStaticCollidersSpatialHash();
	HandleLocalPlayerHotkeys();
}

void S_DebugHelper::LateUpdate() {
	LogEngineBenchmark();
}