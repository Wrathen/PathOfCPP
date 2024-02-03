#include "Scene.h"
#include "Core/Managers/CollisionManager.h"
#include "Core/Miscellaneous/Random.h"
#include "Core/Game/Entity/Entities.h"
#include "Core/Game/Entity/Monsters.h"
#include "Core/Game/Entity/NPCs.h"
#include "Core/Game/System/S_MoveEntities.h"

namespace Core {
	BaseScene::BaseScene() : BaseScene("Zone_Empty.PZD") {}
	BaseScene::BaseScene(const std::string& _zoneDataPath) : BaseScene(_zoneDataPath, "Unnamed BaseScene") {}
	BaseScene::BaseScene(const std::string& _zoneDataPath, const std::string& _name) : zoneDataPath(_zoneDataPath), name(_name) {}

	void BaseScene::Start() { 
		LoadZone();

		// Add all the necessary systems for a generic Core::BaseScene.
		AddSystem<S_MoveEntities>();
	}
	void BaseScene::Update() { 
		for (auto& system : activeSystems)
			system.get()->Update();
	}
	void BaseScene::LateUpdate() {
		for (auto& system : activeSystems)
			system.get()->LateUpdate();
	}
	void BaseScene::Clear() {
		for (auto& system : activeSystems)
			system.get()->Destroy();

		reg.clear();
	}

	void BaseScene::LoadZone() {
		// Load and parse Zone data file.
		Zone zone = Zone::FromSaveFile("../Assets/Zones/" + zoneDataPath);
		name = zone.GetGeneralData().name;

		// Set SpawnManager Variables, Add Entities and SpawnZones
		Reset();
		SetMonsterLevel(zone.GetGeneralData().monsterLevel);
		SpawnPlayer(zone.GetGeneralData().playerSpawnPosition.x, zone.GetGeneralData().playerSpawnPosition.y);
		AddNPCs(zone.GetEntities());
		AddSpawnZones(zone.GetSpawnZones());
		AddPortals(zone.GetPortals());

		// Instantiate Static Colliders
		AddStaticColliders(zone.GetColliders());
	}

	entt::entity BaseScene::SpawnEntity() {
		return reg.create();
	}
	entt::entity BaseScene::SpawnPlayer(float posX, float posY) {
		++totalNumberOfSpawnedPlayers;
		return CreatePlayer(this, posX, posY).GetRaw();
	}
	entt::entity BaseScene::SpawnNPC(float posX, float posY, int type) {
		// Do some statistics :^)
		++totalNumberOfSpawnedNPCs; 
		
		// Create the NPC based on its type ID.
		return (type == 0) ? CreateMerchant(this, posX, posY).GetRaw()   :
			   (type == 1) ? CreateGambler(this, posX, posY).GetRaw()   :
							 CreateBlacksmith(this, posX, posY).GetRaw();
	}
	entt::entity BaseScene::SpawnMonster(float posX, float posY) {
		// Do some statistics :^)
		++totalNumberOfSpawnedMonsters;

		return CreateRandomMonster(this, posX, posY, monsterLevel).GetRaw();
	}
	entt::entity BaseScene::SpawnMonsterInZone(const ZoneSpawnZoneData& zone) {
		auto randomOffset = RandomVector((float)zone.w, (float)zone.h);
		return SpawnMonster(zone.position.x + randomOffset.x - 2000,
							zone.position.y + randomOffset.y - 2000);
	}

	void BaseScene::AddNPCs(const std::vector<ZoneEntityData>& entityData) {
		entities = entityData;

		for (const ZoneEntityData& npc : entities)
			SpawnNPC(npc.position.x - 2000, npc.position.y - 2000, npc.ID);
	}
	void BaseScene::AddSpawnZones(const std::vector<ZoneSpawnZoneData>& spawnZoneData) {
		spawnZones = spawnZoneData;
		// @todo this should be a stat of zones. think like map multipliers.
		uint32_t monsterMultiplier = 2;

		for (const ZoneSpawnZoneData& spawnZone : spawnZones)
			for (uint32_t i = 0; i < spawnZone.amount * monsterMultiplier; ++i)
				SpawnMonsterInZone(spawnZone);
	}
	void BaseScene::AddPortals(const std::vector<ZonePortalData>& portalData) {
		for (const ZonePortalData& portal : portalData)
			CreatePortal(this, portal.position.x, portal.position.y, portal.w, portal.h, portal.nextZone);
	}
	void BaseScene::AddStaticColliders(const std::vector<ZoneColliderData>& colliderData) { CollisionMgr.AddStaticColliders(colliderData); }
	void BaseScene::Reset() {
		monsterLevel = 1;
		totalNumberOfSpawnedNPCs = 0;
		totalNumberOfSpawnedMonsters = 0;
		totalNumberOfSpawnedPlayers = 0;
	}
}