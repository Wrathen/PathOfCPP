#pragma once
#include <string>
#include <unordered_map>
#include "Core/Game/Scene/Scene.h"

namespace Core {
	#define SceneMgr SceneManager::GetInstance()
	class SceneManager {
	public:
		static SceneManager& GetInstance() { static SceneManager _i; return _i; }
		void AddScenes(std::vector<BaseScene*> scenes);
		void ChangeScene(const std::string& name);
		BaseScene* GetCurrentScene();

	protected:
		std::unordered_map<std::string, BaseScene*> sceneList;
		BaseScene* currentScene = nullptr;

		SceneManager() {}
		~SceneManager() {};
		SceneManager(SceneManager const&) = delete;
		void operator=(SceneManager const&) = delete;
	};
}