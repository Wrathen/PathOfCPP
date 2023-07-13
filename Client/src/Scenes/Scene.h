#pragma once
#include "../UI/Background.h"
#include "../UI/SceneTitleBar.h"
#include "../Managers/GameManager.h"
#include "../Managers/EntityManager.h"
#include "../Managers/UIManager.h"
#include "../Managers/EnemySpawnManager.h"
#include "../Game/Zone/Zone.h"

class Scene {
public:
	typedef Scene Super;

	std::string name;
	std::string zoneDataPath;

	SceneTitleBar* sceneTitleBar = nullptr;
	Timer sceneTitleVisibilityTimer;
	Background background;

	Scene() : Scene("Zone_Empty.PZD") {};
	Scene(std::string _zoneDataPath) : name("Uninitialized Scene"), zoneDataPath(_zoneDataPath) {};

	virtual void Start() {
		LoadZone();

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

	void LoadZone() {
		// Load and parse Zone data file.
		Zone zone = Zone::FromSaveFile(zoneDataPath);
		name = zone.GetGeneralData().name;

		// Set Background
		background.SetProperties(zone.GetBackground().bgPath, GAME.screenWidth, GAME.screenHeight); // assets/bg1.png
		background.renderer.UpdateTextureDimensions();

		// Set GameManager Variables
		GAME.zoneWidth = background.renderer.GetWidth();
		GAME.zoneHeight = background.renderer.GetHeight();

		// Set EnemySpawner Variables
		EnemySpawner.SetMonsterLevel(zone.GetGeneralData().monsterLevel);
		//EnemySpawner.SetSpawnAmount(zone.GetGeneralData().GetSpawnAmount());
		//EnemySpawner.SetMaxSpawnAmount(zone.GetGeneralData().GetMaxSpawnAmount());
		//EnemySpawner.SetSpawnInterval(zone.GetGeneralData().GetSpawnInterval());
		EnemySpawner.Reset();

		// Spawn NPC's.
		for (const ZoneEntityData& entity : zone.GetEntities())
			EnemySpawner.SpawnNPC(entity.ID, entity.position.x - 2000, entity.position.y - 2000);
	}
};