#pragma once
#include <string>
#include <unordered_map>
#include "../Miscellaneous/Singleton.h"
#include "../Scenes/Scene.h"

#define SceneMgr SceneManager::GetInstance()
class SceneManager : public Singleton<SceneManager> { friend class Singleton;
private:
	std::unordered_map<std::string, Scene*> sceneList;
	Scene* currentScene = nullptr;

public:
	void Init();
	void ChangeScene(const std::string& name);
	Scene* GetCurrentScene();

	// Events
	void OnPlayerDeath();

private:
	SceneManager() {}
	~SceneManager() {};
	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;
};