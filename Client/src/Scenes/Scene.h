#pragma once
#include "../UI/Background.h"
#include "../UI/SceneTitleBar.h"
#include "../Managers/GameManager.h"
#include "../Managers/EntityManager.h"
#include "../Managers/UIManager.h"

class Scene {
public:
	typedef Scene Super;

	std::string name;
	SceneTitleBar* sceneTitleBar = nullptr;
	Timer sceneTitleVisibilityTimer;
	Background background;

	Scene() : Scene("Unnamed Scene") {};
	Scene(std::string _name) : name(_name) {};

	virtual void Start() {
		sceneTitleBar = new SceneTitleBar();
		sceneTitleVisibilityTimer.Reset();
		sceneTitleBar->SetTitle(name);
	};
	virtual void Update() {
		background.Render();

		if (sceneTitleVisibilityTimer.GetTimeMS() < 3000) 
			sceneTitleBar->Render();
	};
	virtual void LateUpdate() {};
	virtual void Clear() {
		auto& allEntities = *EntityMgr.GetAll();
		for (auto& entity : allEntities)
			if (entity->isToBeDeletedOnSceneChange)
				entity->Delete();

		auto& allUIElements = *UIMgr.GetAll();
		for (auto& element : allUIElements)
			if (element->isToBeDeletedOnSceneChange)
				element->Delete();
	};
};