#include "S_DebugHelper.h"
#include "Miscellaneous/Utils.h"
#include "Game/Component/Components.h"
#include "Core/Managers/CollisionManager.h"
#include "Managers/InputManager.h"
#include "Managers/GameManager.h"

void DrawPlayerCollider() {
	auto localPlayer = Utils::GetLocalPlayer();
	auto pos = Utils::GetScreenPosition(localPlayer.GetComponent<TransformComponent>());
	Utils::FillRect(pos.x - 8, pos.y - 8, 16, 16, { 0, 255, 0, 255 });
}
void DrawStaticColliders() {
	for (auto& data : Core::CollisionMgr.staticColliders) {
		auto colPos = Utils::GetScreenPosition(data.position);
		Utils::FillRect(colPos.x - 2000, colPos.y - 2000, data.w, data.h, { 127, 0, 255, 255 });
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
	DrawStaticColliders();
	HandleLocalPlayerHotkeys();
}

void S_DebugHelper::LateUpdate() {
	LogEngineBenchmark();
}