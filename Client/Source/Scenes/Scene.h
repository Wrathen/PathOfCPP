#pragma once
#include "../UI/Background.h"
#include "../UI/SceneTitleBar.h"
#include "../Managers/GameManager.h"
#include "../Managers/EntityManager.h"
#include "../Managers/UIManager.h"
#include "../Managers/CollisionManager.h"
#include "../Managers/EnemySpawnManager.h"
#include "../Game/Zone/Zone.h"
#include "../Entities/NPCs/Portal.h"
#include "../Game/League/Breach/BreachLeague.h"

class Scene {
public:
	typedef Scene Super;

	std::string name;
	std::string zoneDataPath;

	SceneTitleBar* sceneTitleBar = nullptr;
	Timer sceneTitleVisibilityTimer;
	Background background;

	// Leagues can be placed in here later on, probably, idk.
	BreachLeague breachLeague;

	Scene(): Scene("Zone_Empty.PZD") {};
	Scene(std::string _zoneDataPath): name("Uninitialized Scene"), zoneDataPath(_zoneDataPath) {};

	virtual void Start() {
		// Load Zone Data
		LoadZone();

		// Set-up title bar that is shown on middle-top of the screen.
		sceneTitleBar = new SceneTitleBar();
		sceneTitleVisibilityTimer.Reset();
		sceneTitleBar->SetTitle(name);

		// @todo temp
		breachLeague.Init();
	};
	virtual void Update() {
		background.Render();

		if (sceneTitleVisibilityTimer.GetTimeMS() < 3000)
			sceneTitleBar->Render();
		
		breachLeague.Update();
	};
	virtual void LateUpdate() {};
	virtual void Clear() {
		// Clear all the entities and UIElements that should be deleted on scene changed.
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
		Zone zone = Zone::FromSaveFile("Assets/Zones/" + zoneDataPath);
		name = zone.GetGeneralData().name;

		// Set position of the player to origin.
		GAME.GetPlayer()->transform.SetPosition(zone.GetGeneralData().playerSpawnPosition);

		// Set Background
		background.SetProperties(zone.GetBackground().bgPath, GAME.screenWidth, GAME.screenHeight);
		background.renderer.UpdateTextureDimensions();

		// Set GameManager Variables
		GAME.zoneWidth = background.renderer.GetWidth();
		GAME.zoneHeight = background.renderer.GetHeight();

		// Set EnemySpawner Variables, Add Entities and SpawnZones
		EnemySpawner.Reset();
		EnemySpawner.SetMonsterLevel(zone.GetGeneralData().monsterLevel);
		EnemySpawner.AddNPCs(zone.GetEntities());
		EnemySpawner.AddSpawnZones(zone.GetSpawnZones());

		// Instantiate Static Colliders
		CollisionMgr.AddStaticColliders(zone.GetColliders());

		// Instantiate Portals
		for (const ZonePortalData& portal : zone.GetPortals())
			(new Portal(portal))->transform.SetPosition(portal.position.x + portal.w / 2 - 2000,
														portal.position.y + portal.h / 2 - 2000);
	}
};