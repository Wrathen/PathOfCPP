#include "SceneManager.h"
#include "Core/Miscellaneous/Log.h"
#include "Core/Managers/CollisionManager.h"

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

		// Clear the old scene.
		auto oldScene = currentScene;
		if (oldScene) {
			oldScene->Clear();
			oldScene->isActive = false;
		}

		// Update current scene with the new one.
		currentScene = sceneList[name];
		currentScene->isActive = true;

		// Start the new current scene if it didnt start already.
		if (!currentScene->isLoaded) {
			currentScene->Start();
			currentScene->isLoaded = true;
		}

		// Update the Static Colliders.
		CollisionMgr.AddStaticColliders(currentScene->GetZone().GetColliders());
	}

	BaseScene* SceneManager::GetCurrentScene() { return currentScene; }
}
