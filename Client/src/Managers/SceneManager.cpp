#include "SceneManager.h"
#include "../Scenes/Scene_Town.h"
#include "../Scenes/Scene_Forest.h"
#include "../Scenes/Scene_DefiledCathedral.h"
#include "../Miscellaneous/Log.h"

void SceneManager::Init() {
	sceneList["Town"] = new Scene_Town();
	sceneList["Forest"] = new Scene_Forest();
	sceneList["DefiledCathedral"] = new Scene_DefiledCathedral();
}
void SceneManager::ChangeScene(const std::string& name) {
	if (sceneList.count(name) == 0) {
		Warn("Scene not found! " + name);
		return;
	}

	if (currentScene) currentScene->Clear();
	currentScene = sceneList[name];
	currentScene->Start();
}

Scene* SceneManager::GetCurrentScene() { return currentScene; }

// Events
void SceneManager::OnPlayerDeath() {
	ChangeScene("Town");

	Player* player = GAME.GetPlayer();
	player->CStats->ResetPowerUps();
	player->CHealth->SetHealth(player->CHealth->GetBaseMaxHealth());
}