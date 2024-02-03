#include "SceneManager.h"
#include "Core/Miscellaneous/Log.h"

namespace Core {
	void SceneManager::AddScenes(std::vector<BaseScene*> scenes) {
		for (size_t i = 0; i < scenes.size(); ++i)
			sceneList[scenes[i]->name] = scenes[i];
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

	BaseScene* SceneManager::GetCurrentScene() { return currentScene; }
}