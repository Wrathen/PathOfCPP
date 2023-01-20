#pragma once
#include "../UI/Background.h"
#include "../Managers/GameManager.h"
#include "../Managers/EntityManager.h"
#include "../Managers/UIManager.h"

class Scene {
public:
	Background background;

	virtual void Start() {};
	virtual void Update() {};
	virtual void LateUpdate() {};
	virtual void Clear() {
		Player* player = GAME.GetPlayer();

		auto& allEntities = *EntityMgr.GetAll();
		for (auto entity : allEntities)
			if (entity != player) entity->Delete();

		auto& allUIElements = *UIMgr.GetAll();
		for (auto& element : allUIElements)
			element->Delete();
	};
};